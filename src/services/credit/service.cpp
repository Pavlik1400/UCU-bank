#include "credit/service.h"
#include "account/utils.h"


namespace credit {
    Service::Service(const nlohmann::json &cnf)
            : BasicMicroservice(cnf["credit"]["rpc_port"].get<int>(),
                                "tcp://" + cnf["credit"]["reddis_address"].get<std::string>() + ":"
                                + std::to_string(cnf["credit"]["reddis_port"].get<int>())),
              transactionClient(cnf),
              userClient(cnf["user"]["rpc_address"].get<std::string>(), cnf["user"]["rpc_port"].get<int>()),
              accountClient(cnf["account"]["rpc_address"].get<std::string>(), cnf["account"]["rpc_port"].get<int>()),
              uri("mongodb://" + cnf["mongo"]["address"].get<std::string>() + ":"
                  + cnf["mongo"]["port"].get<std::string>() + "/?replicaSet="
                  + cnf["mongo"]["replicaSet"].get<std::string>()), cnf(cnf), timer_(io_, posix_time::seconds(5)) {

        db = client["bank"];
        credits_collection = db["credits"];
        credits_collection.create_index(session, document{} << credit::ID << 1 << finalize);
        credits_collection.create_index(session, document{} << credit::USER_ID << 1 << finalize);

        db_for_thread = client_for_thread["bank"];
        credits_collection_for_thread = db_for_thread["credits"];

        wc_majority.acknowledge_level(mongocxx::write_concern::level::k_majority);
        rc_local.acknowledge_level(mongocxx::read_concern::level::k_local);
        rp_primary.mode(mongocxx::read_preference::read_mode::k_primary);
        sopts.write_concern(wc_majority);
        sopts.read_concern(rc_local);
        sopts.read_preference(rp_primary);

        user_t super_user_tmp {
            "",
            "super",
            "do_you_wanna_have_a_bad_time_?",
            "come_on_found_me_if_you_can",
            "2022-10-10",
            "0000000000",
            "do_you_wanna_have_a_bad_time@do_you_wanna_have_a_bad_time.sans.com",
            "lvivski kruasany",
            "kruasan",
        };
        userClient.create(super_user_tmp);
        auto [st, super_inst] = userClient.get<user::by::PHONE_NO>("0000000000", {"", user::privilege::SUPER});
        super_user = super_inst;
        accountClient.create(super_user.id, "", {"", user::privilege::SUPER});
        auto [st1, super_inst_acc_v] = accountClient.get_all(super_user.id, {"", user::privilege::SUPER});
        super_user_acc = super_inst_acc_v[0];

        credit_update_period = cnf["credit"]["credit_update_period"].get<int>();
        credit_update_measure = cnf["credit"]["credit_update_measure"].get<std::string>();

        timer_.async_wait([&](const boost::system::error_code&) { credit_scheduled_job(); });
        worker_threads.create_thread([ObjectPtr = &io_] { ObjectPtr->run(); });

        CUSTOM_LOG(lg, debug) << "Credit service initialized";
    }


    void Service::start() {
        rpc_server.bind(method::CREATE, [&](const std::string &user_id, const std::string &card, const int credit_type, const double balance, const auth::AuthDU &ctrl) {
            return create(user_id, card, credit_type, balance, ctrl);
        });
        rpc_server.bind(method::GET_ALL, [&](const std::string &user_id, const auth::AuthDU &ctrl) {
            return get_all(user_id, ctrl);
        });
        rpc_server.bind(method::FINISH_CREDIT, [&](const std::string &user_id, const std::string &credit_id, const auth::AuthDU &ctrl) {
            return finish_credit(user_id, credit_id, ctrl);
        });
        CUSTOM_LOG(lg, info) << "Service started successfully";
    }

    void Service::finish() {
        CUSTOM_LOG(lg, info) << "Service has finished";
    }

    credit::status Service::create(const std::string &user_id, const std::string &card, const int credit_type, const double balance, const auth::AuthDU &ctrl) {
        CUSTOM_LOG(lg, debug) << "Create call";
        if (user_id != ctrl.cred && ctrl.data != user::privilege::SUPER) {
            return credit::status::NOT_ENOUGH_PRIVILEGES;
        }
        if (userClient.valid_id(user_id) == user::status::USER_DOESNT_EXIST) {
            return credit::status::INVALID_USER_ID;
        }
        if (accountClient.exists(card) != account::status::OK) {
            return credit::status::INVALID_ACCOUNT_ID;
        }
        auto credit_id = generate_card_token();

        // generate unique card number
        while (credits_collection.find_one(session, document{} << credit::ID << credit_id << finalize)) {
            credit_id = generate_card_token();
        }

        transaction_t trans{
                super_user.id,
                super_user_acc.number,
                card,
                "Credit income transaction",
                balance,
                transaction::category::CREDIT_TRANSACTION
        };
        auto tr_status = transactionClient.create(trans, {.data=user::privilege::SUPER});
        if (tr_status) {
            CUSTOM_LOG(lg, warning) << "Transaction failed: " << tr_status;
            return credit::status::TRANSACTION_FAILED;
        }

        auto doc =
                document{} << credit::ID << credit_id << credit::USER_ID << user_id
                        << credit::CARD_NUMBER << card << credit::OPENING_DATE << generate_current_datetime()
                        << credit::ACTIVE << true << credit::ORIGINAL_BALANCE << balance
                        << credit::CURRENT_BALANCE << balance
                        << credit::PERCENT << credit::CREDIT_TYPES[credit_type].second
                        << credit::PERIOD << credit::CREDIT_TYPES[credit_type].first << finalize;
        auto status = credits_collection.insert_one(session, doc.view());

        if (!status) {
            transaction_t trans_revert{
                    super_user_acc.number,
                    super_user.id,
                    card,
                    "Credit revert transaction",
                    balance,
                    transaction::category::CREDIT_TRANSACTION
            };
            transactionClient.create(trans_revert, {.data=user::privilege::SUPER});
        }

        return status ? credit::status::OK : credit::status::CREATION_FAILED;
    }

    std::pair<credit::status, std::vector<credit_t>> Service::get_all(const std::string &user_id, const auth::AuthDU &ctrl) {
        CUSTOM_LOG(lg, debug) << "Get all call";
        if (userClient.valid_id(user_id) == user::status::USER_DOESNT_EXIST) {
            return {credit::status::INVALID_USER_ID, {}};
        }

        auto result = credits_collection.find(session, document{} << credit::USER_ID << user_id << finalize);
        std::vector<credit_t> credits{};
        for (auto &info: result) {
            credit_t account;
            try {
                account = std::move(deserialize(info, ctrl));
            } catch (const std::exception &exc) {
                CUSTOM_LOG(lg, error) << "get failed: \n" << exc.what();
                return {credit::status::GET_FAILED, {}};
            }
            credits.push_back(account);
        }

        return {credit::status::OK, credits};
    }

    credit::status Service::finish_credit(const std::string &user_id, const std::string &credit_id, const auth::AuthDU &ctrl) {
        CUSTOM_LOG(lg, debug) << "Finish credit call";
        if (user_id != ctrl.cred && ctrl.data != user::privilege::SUPER) {
            return credit::status::NOT_ENOUGH_PRIVILEGES;
        }
        if (userClient.valid_id(user_id) == user::status::USER_DOESNT_EXIST) {
            return credit::status::INVALID_USER_ID;
        }

        auto result = credits_collection.find_one(session, document{} << credit::ID << credit_id << finalize);
        credit_t credit_inst;
        if (result) {
            try {
                credit_inst = std::move(deserialize(result->view(), ctrl));
            } catch (const std::exception &exc) {
                CUSTOM_LOG(lg, error) << "get failed: \n" << exc.what();
                return credit::status::GET_FAILED;
            }
        }

        if (accountClient.get(credit_inst.card_number, {"", user::privilege::SUPER}).second.balance < credit_inst.current_balance) {
            return credit::status::NOT_ENOUGH_MONEY;
        }

        transaction_t trans{
                super_user.id,
                credit_inst.card_number,
                super_user_acc.number,
                "Credit transaction",
                credit_inst.current_balance,
                transaction::category::CREDIT_TRANSACTION
        };
        auto tr_status = transactionClient.create(trans, {.data=user::privilege::SUPER});
        if (tr_status) {
            CUSTOM_LOG(lg, warning) << "Transaction failed: " << tr_status;
            return credit::status::TRANSACTION_FAILED;
        }

        return reduce_credit_amount(credit_inst, credit_inst.current_balance, credits_collection, session);
    }

    credit_t Service::deserialize(const bsoncxx::document::view &info, const auth::AuthDU &ctrl) {
        credit_t credit_inst{};
        auto credit_id = info[credit::ID].get_utf8().value.to_string();
        auto user_id = info[credit::USER_ID].get_utf8().value.to_string();
        credit_inst.card_number = info[credit::CARD_NUMBER].get_utf8().value.to_string();
        credit_inst.active = info[credit::ACTIVE].get_bool();

        if (ctrl.cred == user_id || ctrl.data == user::privilege::ADMIN || ctrl.data == user::privilege::SUPER) {
            credit_inst.id = credit_id;
            credit_inst.user_id = user_id;
            credit_inst.opening_date = info[credit::OPENING_DATE].get_utf8().value.to_string();
            credit_inst.original_balance = info[credit::ORIGINAL_BALANCE].get_double();
            credit_inst.current_balance = info[credit::CURRENT_BALANCE].get_double();
            credit_inst.percent = info[credit::PERCENT].get_double();
            credit_inst.period = info[credit::PERIOD].get_int32();
        }
        return credit_inst;
    }

    credit::status Service::reduce_credit_amount(const credit_t &credit_inst, const double amount, mongocxx::collection &coll, mongocxx::client_session &client_sess) {
        bool status;
        mongocxx::client_session::with_transaction_cb callback = [&](mongocxx::client_session *) {
            auto status1 = coll.update_one(client_sess, document{} << credit::ID << credit_inst.id << finalize,
                                                         document{} << INC << open_document << credit::CURRENT_BALANCE << -1 * amount
                                                                    << close_document << finalize);
            if (amount >= credit_inst.current_balance - 0.05) {
                auto status2 = coll.update_one(client_sess, document{} << credit::ID << credit_inst.id << finalize,
                                                             document{} << SET << open_document << credit::ACTIVE << false
                                                                        << close_document << finalize);
                if (!status2->modified_count()) {
                    coll.update_one(client_sess, document{} << credit::ID << credit_inst.id << finalize,
                                                  document{} << SET << open_document << credit::ACTIVE << true
                                                             << close_document << finalize);
                }
            }
            if (!status1->modified_count()) {
                coll.update_one(client_sess, document{} << credit::ID << credit_inst.id << finalize,
                                              document{} << INC << open_document << credit::CURRENT_BALANCE << amount
                                                         << close_document << finalize);
                status = false;
                return;
            }
            status = true;
        };
        try {
            client_sess.with_transaction(callback, sopts);
        } catch (const mongocxx::exception &e) {
            CUSTOM_LOG_SAFE(lg, error) << "An exception occurred: " << e.what() << "\n";
            return credit::status::TRANSACTION_FAILED;
        }

        return status ? credit::status::OK : credit::status::TRANSACTION_FAILED;
    }

    void Service::credit_scheduled_job() {
        CUSTOM_LOG_SAFE(lg, info) << "Started credit update job";

        auto result = credits_collection_for_thread.find(session_for_thread, document{} << credit::ACTIVE << true << finalize);
        std::vector<credit_t> credits{};
        for (auto &info: result) {
            credit_t account;
            try {
                account = std::move(deserialize(info, {.data=user::privilege::SUPER}));
            } catch (const std::exception &exc) {
                CUSTOM_LOG_SAFE(lg, error) << "get failed: \n" << exc.what();
            }
            credits.push_back(account);
        }

        for (const auto& credit_ : credits) {
            double amount_to_get = (credit_.original_balance / credit_.period) + (credit_.original_balance * credit_.percent / 100);
            double amount = credit_.original_balance / credit_.period;

            transaction_t trans{
                    super_user.id,
                    credit_.card_number,
                    super_user_acc.number,
                    "Credit transaction",
                    amount_to_get,
                    transaction::category::CREDIT_TRANSACTION
            };
            auto tr_status = transactionClient.create(trans, {.data=user::privilege::SUPER});
            if (tr_status) {
                CUSTOM_LOG_SAFE(lg, warning) << "Transaction failed: " << tr_status;
                continue;
            }
            if (reduce_credit_amount(credit_, amount, credits_collection_for_thread, session_for_thread) == credit::status::TRANSACTION_FAILED) {
                CUSTOM_LOG_SAFE(lg, error) << "Update credit failed";
                transaction_t trans_revert{
                        super_user.id,
                        super_user_acc.number,
                        credit_.card_number,
                        "Credit transaction revert",
                        amount_to_get,
                        transaction::category::CREDIT_TRANSACTION
                };
                transactionClient.create(trans, {.data=user::privilege::SUPER});
            }
        }

        timer_.expires_at(timer_.expires_at() + posix_time::seconds(credit_update_period));
        timer_.async_wait([&](const boost::system::error_code&) { credit_scheduled_job(); });
    }
}