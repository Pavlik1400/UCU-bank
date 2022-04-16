#ifndef UCU_BANK_STATUC_HPP
#define UCU_BANK_STATUC_HPP

#include <optional>
#include <pqxx/pqxx>
#include <rpc/msgpack.hpp>
#include "service_tools/utils.hpp"


using str = std::string;

namespace transaction {
    static const unsigned long long select_query_max_limit = 100;
    static const std::string &db_config_path = "configs/transaction_db.json";
    namespace tables {
        static const std::string &money_transfer = "account_money_transfer";
    }

    enum status {
        OK = 0,
        FORBIDEN = 1,
        ACCOUNT_DOESNT_EXISTS = 2,
        FAILED = 3,
        IS_NOT_LOGINED = 4,
        NOT_ENOUGH_MONEY = 5,
        FILTER_LIMIT_EXCEEDED = 6,
    };

    enum db_entry_status {
        JUST_ADDED = 0,
        VERIFIED = 1,
        FINISHED = 2,
    };

    enum categories {
        CAFE_AND_RESTAURANTS,
        SALARY,
        TECH_EQUIPMENT,
        HOUSEHOLD_EQUIPMENT,
        OTHER_INCOME,
        ATM,
        PRODUCTS,
        GASOLINE,
        ENTERTAINMENT,
        CARD_TRANSFER,
    };
}

MSGPACK_ADD_ENUM(transaction::status)
MSGPACK_ADD_ENUM(transaction::db_entry_status)
MSGPACK_ADD_ENUM(transaction::categories)

struct Transaction {
    // those fields are required when adding transaction
    str user_id;
    str from_acc_number;
    str to_acc_number;
    str description;
    double amount{};
    transaction::categories category;

    // those are filled only in select query
    ucu_optional<std::string> date;
    ucu_optional<transaction::db_entry_status> status;

    MSGPACK_DEFINE (user_id, from_acc_number, to_acc_number, description, amount, category, date, status);


public:
    Transaction(str user_id, str from_acc_number, str to_acc_number, str description, double amount,
                transaction::categories category);

    Transaction();

private:
    Transaction(str user_id, str from_acc_number, str to_acc_number, str description, double amount,
                transaction::categories category, str date, transaction::db_entry_status status);

public:
    inline friend std::ostream &operator<<(std::ostream &os, const Transaction &tran) {
        os << "Account(num=" << tran.from_acc_number << ") --(" << tran.amount
           << "$)>> Account(num=" << tran.to_acc_number << ")";
        return os;
    }

public:
    static Transaction from_row(const pqxx::row &row);
};

struct TransactionFilter {
    std::string from_acc_number;
    unsigned long long limit;
    ucu_optional<std::string> to_acc_number;
    ucu_optional<std::string> from_date;
    ucu_optional<std::string> to_date;
    ucu_optional<double> min_amount;
    ucu_optional<double> max_amount;
    ucu_optional<transaction::categories> category;
    ucu_optional<std::string> description;
    MSGPACK_DEFINE (from_acc_number, limit, to_acc_number, from_date, to_date, min_amount, max_amount, category,
                    description);

};

#endif //UCU_BANK_STATUC_HPP
