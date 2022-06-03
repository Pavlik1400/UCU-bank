#include "transaction/service.hpp"
#include "account/constants.h"
#include "service_tools/utils.hpp"
#include "user/constants.h"
#include <sstream>

namespace transaction {
    Service::Service(const nlohmann::json &cnf) :
            BasicMicroservice(cnf["transaction"]["rpc_port"].get<int>(),
                              "tcp://" + cnf["transaction"]["reddis_address"].get<std::string>() +
                              ":" + std::to_string(cnf["transaction"]["reddis_port"].get<int>())),
            account_client(cnf["account"]["rpc_address"].get<std::string>(),
                           cnf["account"]["rpc_port"].get<int>()),
            notification_client(cnf["notification"]["broker_address"].get<std::string>() + ":" + cnf["notification"]["broker_port"].get<std::string>(), cnf["notification"]["topic"].get<std::string>()),
            cnf(cnf), pq_connection({}) {
        CUSTOM_LOG(lg, debug) << "Transaction service initialized";
    }


    void Service::start() {
        try {
            auto db_config = cnf["transaction"]["db"];
//        auto connection_string =
//        std::cerr << "connection_string: \n" << connection_string << std::endl;
            pq_connection = pq::connection(
//                connection_string
                    "dbname = " + db_config.at("dbname").get<const std::string>() +
                    " user = " + db_config.at("user").get<const std::string>() +
                    " password = " + db_config.at("password").get<const std::string>() +
                    " host = " + db_config.at("host").get<const std::string>() +
                    " port = " + db_config.at("port").get<const std::string>()
            );
            if (pq_connection.value().is_open()) {
                CUSTOM_LOG(lg, info) << "Opened db " << pq_connection.value().dbname() << " successfully";
            } else {
                throw std::runtime_error{"Can't open database"};
            }
        } catch (const std::exception &exc) {
            CUSTOM_LOG(lg, fatal) << "Error while initializing database connection: \n" << exc.what();
            exit(1);
        }
        register_methods();
        CUSTOM_LOG(lg, info) << "Transaction service started";
    }

    void Service::finish() {
        try {
            pq_connection.value().close();
        } catch (const std::exception &exc) {
            CUSTOM_LOG(lg, error) << "Database close is unsuccessfull: \n" << exc.what();
        }
        CUSTOM_LOG(lg, info) << "Transcation service finished";
    }

    transaction::status Service::make_transaction(const transaction_t &tran, const auth::AuthDU &privilege) {
        CUSTOM_LOG(lg, debug) << "create " << tran;

        std::stringstream ss; ss << tran;
        notification_client.send(notification_t{.identifier=tran.from_acc_number,
                                                .payload=ss.str(),
                                                .type=identifier_type::CARD_NUMBER});
        notification_client.send(notification_t{.identifier=tran.to_acc_number,
                                                .payload=ss.str(),
                                                .type=identifier_type::CARD_NUMBER});

        auto [status, entry_id] = add_transaction_to_db(tran, transaction::JUST_ADDED);
        CUSTOM_LOG(lg, debug) << "Transaction " << tran << " has id " << entry_id;
        if (status != transaction::OK) return status;
        if ((status = verify_transaction(tran, privilege)) != transaction::OK) {
            CUSTOM_LOG(lg, info) << "Transaction with id: " << entry_id << " is not verified with status "
                                 << status_to_str(status);
            delete_transaction(entry_id);
            return status;
        }
        if ((status = update_transaction_status(entry_id, transaction::VERIFIED)) != transaction::OK) {
            delete_transaction(entry_id);
            return status;
        }
        auto tran_status = account_client.transaction(tran.from_acc_number, tran.to_acc_number, tran.amount);
        if (tran_status != account::status::OK) {
            CUSTOM_LOG(lg, info) << "Transaction with id: " << entry_id << " failed in Account";
            delete_transaction(entry_id);
            return transaction::status::FAILED;
        }
        if ((status = update_transaction_status(entry_id, transaction::FINISHED)) != transaction::OK) {
            account_client.transaction(tran.from_acc_number, tran.to_acc_number, -tran.amount);  // return money
            delete_transaction(entry_id);
            return transaction::status::FAILED;
        }
        return transaction::status::OK;
    }

    transaction::status Service::verify_transaction(const transaction_t &tran, const auth::AuthDU &privilege) {
        // TODO: check if user is loggined - Auth serice
//    if (!auth_rpc.is_logined(tran.user_id)) {
//        return TransactionStatus::IS_NOT_LOGINED;
//    }
        CUSTOM_LOG(lg, debug) << "Verifying transaction: " << tran;
        auto [status, acc_info] = account_client.get(tran.from_acc_number, {.data=user::privilege::ADMIN});
        if (status != account::status::OK) {
            switch (status) {
                case account::status::INVALID_CARD_NUMBER:
                    return transaction::FROM_ACCOUNT_DOESNT_EXISTS;
                default:
                    return transaction::FAILED;
            }
        }
        auto acc_resp = account_client.get(tran.to_acc_number, {.data=user::privilege::ADMIN});
        if (acc_resp.first != account::status::OK) {
            switch (acc_resp.first) {
                case account::status::INVALID_CARD_NUMBER:
                    return transaction::TO_ACCOUNT_DOESNT_EXISTS;
                default:
                    return transaction::FAILED;
            }
        }

        // check if user has access to this card
        if (acc_info.user_id != tran.user_id && privilege.data != user::privilege::SUPER) {
            return transaction::FORBIDEN;
        }
        // check if account has enough money
        if (acc_info.balance < tran.amount && privilege.data != user::privilege::SUPER) {
            return transaction::NOT_ENOUGH_MONEY;
        }

        return transaction::OK;
    }

    add_transaction_res Service::add_transaction_to_db(
            const transaction_t &tran,
            transaction::db_entry_status status
    ) {
        unsigned long long entry_id;
        if (tran.category >= transaction::category::Count || tran.category < 0) {
            return {transaction::BAD_CATEGORY, -1};
        }
        try {
            std::cout << "Add transaction: from_n = " << tran.from_acc_number << ", to_n = " << tran.to_acc_number << std::endl;
            pq::work work(pq_connection.value());
            auto sql =
                    "INSERT INTO " + transaction::tables::money_transfer +
                    " (from_acc_number, to_acc_number, amount, date, status, description, category) values"
                    " (" +
                    + "'" + work.esc(tran.from_acc_number) + "'," +
                    + "'" + work.esc(tran.to_acc_number) + "'," +
                    work.esc(std::to_string(tran.amount)) + ",'" +
                    work.esc(cur_time_str()) + "'," +
                    work.esc(std::to_string(status)) + ",'" +
                    work.esc(tran.description) + "'," +
                    work.esc(std::to_string(tran.category)) +
                    ") RETURNING id";
            std::cout << "SQL: " << sql << std::endl;
            pq::result insert_res(work.exec(sql));
            entry_id = insert_res.begin()[0].as<unsigned long long>();
            work.commit();
        } catch (const std::exception &exc) {
            CUSTOM_LOG(lg, error) << "Error while inserting transaction: " << tran << ": \n" << exc.what();
            return {transaction::FAILED, -1};
        }
        return {transaction::OK, entry_id};
    }

    transaction::status Service::update_transaction_status(
            unsigned long long entry_id,
            transaction::db_entry_status status
    ) {
        try {
            pq::work work(pq_connection.value());
            auto sql = "UPDATE " + transaction::tables::money_transfer +
                       " SET status = " + work.esc(std::to_string(status)) +
                       " WHERE id=" + work.esc(std::to_string(entry_id));
            work.exec(sql);
            work.commit();

        } catch (const std::exception &exc) {
            CUSTOM_LOG(lg, error) << "Error while updating transaction with id: " << entry_id;
            return transaction::FAILED;
        }
        return transaction::OK;
    }

    transaction::status Service::delete_transaction(unsigned long long int entry_id) {
        try {
            pq::work work(pq_connection.value());
            auto sql = "DELETE FROM " + transaction::tables::money_transfer +
                       " WHERE id=" + work.esc(std::to_string(entry_id));
            work.exec(sql);
            work.commit();

        } catch (const std::exception &exc) {
            CUSTOM_LOG(lg, error) << "Error while deleting transaction with id: " << entry_id;
            return transaction::FAILED;
        }
        return transaction::OK;
    }

    tran_query_res Service::get_transaction(const trans_filter &filter) {
        CUSTOM_LOG(lg, info) << "Get call with filter: " << filter;
        auto status = transaction::status::OK;
        auto limit = filter.limit;
        if (limit > transaction::select_query_max_limit) {
            status = transaction::status::FILTER_LIMIT_EXCEEDED;
            limit = transaction::select_query_max_limit;
        }
        std::vector<transaction_t> query_result;
        query_result.reserve(limit);
        try {
            pq::nontransaction non_tran_work(pq_connection.value());
            auto sql = "SELECT * FROM " + transaction::tables::money_transfer + " WHERE ";
            // from_acc_number
            sql += " from_acc_number = '" + non_tran_work.esc(filter.acc_number) + "'";
            sql += " or to_acc_number = '" + non_tran_work.esc(filter.acc_number) + "'";
            if (filter.from_date) sql += " and date > '" + non_tran_work.esc(filter.from_date.value) + "'::date";
            if (filter.to_date) sql += " and date < '" + non_tran_work.esc(filter.to_date.value) + "'::date";
            if (filter.min_amount) sql += " and amount > " + std::to_string(filter.min_amount.value);
            if (filter.max_amount) sql += " and amount < " + std::to_string(filter.max_amount.value);
            if (filter.category) sql += " and category = " + std::to_string(filter.category.value);
            if (filter.description)
                sql += " and description LIKE '%" + non_tran_work.esc(filter.description.value) + "%'";
            sql += " ORDER BY date";
            sql += " LIMIT " + std::to_string(limit);

            pq::result select_res = non_tran_work.exec(sql);
            for (pq::result::const_iterator c = select_res.begin(); c != select_res.end(); ++c) {
                query_result.push_back(transaction_t::from_row(c));
            }

        } catch (const std::exception &exc) {
            CUSTOM_LOG(lg, error) << "Error in select query: \n" << exc.what();
            return {transaction::FAILED, {}};
        }
        return {status, query_result};
    }

    void Service::register_methods() {
        rpc_server.bind("get", [&](const trans_filter &filter) { return get_transaction(filter); });
        rpc_server.bind("create", [&](const transaction_t &tran, const auth::AuthDU &priv) { return make_transaction(tran, priv); });
    }

    Service::~Service() = default;

}