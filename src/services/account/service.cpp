#include "account/service.h"
#include "account/constants.h"
#include "account/utils.h"
#include "service_tools/utils.hpp"

namespace account {
    void Service::start() {
        register_methods();
        CUSTOM_LOG(lg, info) << "Service started successfully";
    }


    account::status Service::create(const std::string &user_id, const std::string &account_type) {
        CUSTOM_LOG(lg, debug) << "Create call";
        // TODO: add user_id validation
        if (userClient.valid_id(user_id) == user::status::USER_DOESNT_EXIST) {
            return account::status::INVALID_USER_ID;
        }
        auto card = generate_card_token();

        // generate unique card number
        while (accounts.find_one(session, document{} << account::NUMBER << card << finalize)) {
            card = generate_card_token();
        }

        auto doc =
                document{} << account::USER_ID << user_id << account::NUMBER << card << account::CVV << generate_cvv()
                           << account::TYPE << account_type << account::OPENING_DATE << generate_current_datetime()
                           << account::ACTIVE << true << account::BALANCE << 0.0 << finalize;
        auto status = accounts.insert_one(session, doc.view());

        return status ? account::status::OK : account::status::CREATION_FAILED;
    }


    std::pair<account::status, account_t> Service::get(const std::string &card) {
        CUSTOM_LOG(lg, debug) << "Get call";
        auto result = accounts.find_one(session, document{} << account::NUMBER << card << finalize);
        account_t account;

        if (result) {
            try {
                auto content = result->view();
                account.user_id = content[account::USER_ID].get_utf8().value.to_string();
                account.cvv = content[account::CVV].get_utf8().value.to_string();
                account.number = content[account::NUMBER].get_utf8().value.to_string();
                account.type = content[account::TYPE].get_utf8().value.to_string();
                account.opening_date = content[account::OPENING_DATE].get_utf8().value.to_string();
                account.active = content[account::ACTIVE].get_bool();
                account.balance = content[account::BALANCE].get_double();
            } catch (const std::exception &exc) {
                CUSTOM_LOG(lg, error) << "get failed: \n" << exc.what();
                return {account::status::GET_FAILED, {}};
            }

        }

        return {result ? account::status::OK : account::status::INVALID_CARD_NUMBER, account};

    }

    account::status Service::remove(const std::string &card) {
        CUSTOM_LOG(lg, debug) << "Remove call";
        auto status = accounts.delete_one(session, document{} << account::NUMBER << card << finalize);
        return status ? account::status::OK : account::status::INVALID_CARD_NUMBER;

    }

    account::status Service::transaction(const std::string &from, const std::string &to, double amount) {
        CUSTOM_LOG(lg, debug) << "Transaction call";
        bool status;
        mongocxx::client_session::with_transaction_cb callback = [&](mongocxx::client_session*) {
            // Important::  You must pass the session to the operations.
            auto status1 = accounts.update_one(session, document{} << account::NUMBER << from << finalize,
                                               document{} << INC << open_document << account::BALANCE << -1 * amount
                                                          << close_document << finalize);
            auto status2 = accounts.update_one(session, document{} << account::NUMBER << to << finalize,
                                               document{} << INC << open_document << account::BALANCE << amount
                                                          << close_document << finalize);

            if (!status1->modified_count() || !status2->modified_count()) {
                accounts.update_one(session, document{} << account::NUMBER << from << finalize,
                                                   document{} << INC << open_document << account::BALANCE << amount
                                                              << close_document << finalize);
                accounts.update_one(session, document{} << account::NUMBER << to << finalize,
                                                   document{} << INC << open_document << account::BALANCE << -1 * amount
                                                              << close_document << finalize);
                status = false;
                return;
            }
            status = true;
        };

        try {
            session.with_transaction(callback, sopts);
        } catch (const mongocxx::exception& e) {
            CUSTOM_LOG(lg, error) << "An exception occurred: " << e.what() << std::endl;
            return account::status::TRANSACTION_FAILED;
        }
        return status ? account::status::OK : account::status::TRANSACTION_FAILED;
    }


    account::status Service::exists(const std::string &card) {
        CUSTOM_LOG(lg, debug) << "Exists call";
        auto status = accounts.find_one(session, document{} << account::NUMBER << card << finalize);
        return status ? account::status::OK : account::status::INVALID_CARD_NUMBER;

    }

    void Service::register_methods() {
        rpc_server.bind("create", [&](const std::string &user_id, const std::string &account_type) {
            return create(user_id, account_type);
        });
        rpc_server.bind("get", [&](const std::string &card) { return get(card); });
        rpc_server.bind("get_all", [&](const std::string &user_id) { return get_all(user_id); });
        rpc_server.bind("remove", [&](const std::string &card) { return remove(card); });
        rpc_server.bind("exists", [&](const std::string &card) { return exists(card); });
        rpc_server.bind("transaction", [&](const std::string &from, const std::string &to, double amount) {
            return transaction(from, to, amount);
        });

    }

    void Service::finish() {
        CUSTOM_LOG(lg, info) << "Service has finished";
    }

    Service::Service(const nlohmann::json &cnf) :

            BasicMicroservice(cnf["account"]["rpc_port"].get<int>(),
                              "tcp://" + cnf["account"]["reddis_address"].get<std::string>() + ":" +
                              std::to_string(cnf["account"]["reddis_port"].get<int>())),
            userClient(cnf["user"]["rpc_address"].get<std::string>(), cnf["user"]["rpc_port"].get<int>()), cnf(cnf) {

        db = client["bank"];
        accounts = db["accounts"];
        accounts.create_index(session, document{} << account::USER_ID << 1 << finalize);
        accounts.create_index(session, document{} << account::NUMBER << 1 << finalize);
        wc_majority.acknowledge_level(mongocxx::write_concern::level::k_majority);
        rc_local.acknowledge_level(mongocxx::read_concern::level::k_local);
        rp_primary.mode(mongocxx::read_preference::read_mode::k_primary);
        sopts.write_concern(wc_majority);
        sopts.read_concern(rc_local);
        sopts.read_preference(rp_primary);
        CUSTOM_LOG(lg, debug) << "Account service initialized";
    }

    std::pair<account::status, std::vector<account_t>> Service::get_all(const std::string &user_id) {
        CUSTOM_LOG(lg, debug) << "Get all call";
        if (userClient.valid_id(user_id) == user::status::USER_DOESNT_EXIST) {
            return {account::status::INVALID_USER_ID, {}};
        }
        auto result = accounts.find(session, document{} << account::USER_ID << user_id << finalize);
        std::vector<account_t> user_accounts{};
        for(auto& info: result){
            account_t account;
            try {
                account.user_id = info[account::USER_ID].get_utf8().value.to_string();
                account.cvv = info[account::CVV].get_utf8().value.to_string();
                account.number = info[account::NUMBER].get_utf8().value.to_string();
                account.type = info[account::TYPE].get_utf8().value.to_string();
                account.opening_date = info[account::OPENING_DATE].get_utf8().value.to_string();
                account.active = info[account::ACTIVE].get_bool();
                account.balance = info[account::BALANCE].get_double();
            } catch (const std::exception &exc) {
                CUSTOM_LOG(lg, error) << "get failed: \n" << exc.what();
                return {account::status::GET_FAILED, {}};
            }
            user_accounts.push_back(account);
        }

        return {account::status::OK, user_accounts};
    }
}


