#ifndef UCU_BANK_TRANSACTION_CONSTANTS_HPP
#define UCU_BANK_TRANSACTION_CONSTANTS_HPP

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
        BAD_CATEGORY = 7,
        FROM_ACCOUNT_DOESNT_EXISTS = 8,
        TO_ACCOUNT_DOESNT_EXISTS = 9,
    };

    enum db_entry_status {
        JUST_ADDED = 0,
        VERIFIED = 1,
        FINISHED = 2,
    };

    enum category {
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
        Count,
    };

    inline std::string category_to_str(category c) {
        switch (c) {
            case CAFE_AND_RESTAURANTS: return "CAFE_AND_RESTAURANTS";
            case SALARY: return "SALARY";
            case TECH_EQUIPMENT: return "TECH_EQUIPMENT";
            case HOUSEHOLD_EQUIPMENT: return "HOUSEHOLD_EQUIPMENT";
            case OTHER_INCOME: return "OTHER_INCOME";
            case ATM: return "ATM";
            case PRODUCTS: return "PRODUCTS";
            case GASOLINE: return "GASOLINE";
            case ENTERTAINMENT: return "ENTERTAINMENT";
            case CARD_TRANSFER: return "CARD_TRANSFER";
            default: return "EROR";
        }
    }


    inline std::string status_to_str(status s) {
        switch (s) {
            case OK:
                return "OK";
            case FORBIDEN:
                return "FORBIDEN";
            case ACCOUNT_DOESNT_EXISTS:
                return "ACCOUNT_DOESNT_EXISTS";
            case FAILED:
                return "FAILED";
            case IS_NOT_LOGINED:
                return "IS_NOT_LOGINED";
            case NOT_ENOUGH_MONEY:
                return "NOT_ENOUGH_MONEY";
            case FILTER_LIMIT_EXCEEDED:
                return "FILTER_LIMIT_EXCEEDED";
            case BAD_CATEGORY:
                return "BAD_CATEGORY";
            case FROM_ACCOUNT_DOESNT_EXISTS:
                return "FROM_ACCOUNT_DOESNT_EXISTS";
            case TO_ACCOUNT_DOESNT_EXISTS:
                return "TO_ACCOUNT_DOESNT_EXISTS";
            default:
                return "UNKNOWN_ERROR";
        }
    }
}

MSGPACK_ADD_ENUM(transaction::status)
MSGPACK_ADD_ENUM(transaction::db_entry_status)
MSGPACK_ADD_ENUM(transaction::category)

struct transaction_t {
    // those fields are required when adding transaction
    str user_id;
    str from_acc_number;
    str to_acc_number;
    str description;
    double amount;
    transaction::category category;

    // those are filled only in select query
    ucu_optional<std::string> date;
    ucu_optional<transaction::db_entry_status> status;

    MSGPACK_DEFINE (user_id, from_acc_number, to_acc_number, description, amount, category, date, status);


public:
    transaction_t(str user_id, str from_acc_number, str to_acc_number, str description, double amount,
                  transaction::category category);

    transaction_t();

private:
    transaction_t(str user_id, str from_acc_number, str to_acc_number, str description, double amount,
                  transaction::category category, str date, transaction::db_entry_status status);

public:
    inline friend std::ostream &operator<<(std::ostream &os, const transaction_t &tran) {
        os << "Account(num=" << tran.from_acc_number << ") --(" << tran.amount
           << "$)>> Account(num=" << tran.to_acc_number << ")";
        return os;
    }

public:
    static transaction_t from_row(const pqxx::row &row);
};

struct trans_filter {
    std::string acc_number;
    unsigned long long limit;
    ucu_optional<std::string> from_date = {};
    ucu_optional<std::string> to_date = {};
    ucu_optional<double> min_amount = {};
    ucu_optional<double> max_amount = {};
    ucu_optional<transaction::category> category = {};
    ucu_optional<std::string> description = {};
    MSGPACK_DEFINE (acc_number, limit, from_date, to_date, min_amount, max_amount, category,
                    description);

public:
    inline friend std::ostream &operator<<(std::ostream &os, const trans_filter &filter) {
        os << "Filter(acc_number=" << filter.acc_number << ", limit=" << filter.limit << ", from_date="
           << filter.from_date << ", to_date=" << filter.to_date << ", min_amount=" << filter.min_amount
           << ", max_amount=" << filter.max_amount;
        if (filter.category)
            os << ", category=" << transaction::category_to_str(filter.category.value);
        os << ", description=" << filter.description << ")";
        return os;
    };
};

using add_transaction_res = std::pair<transaction::status, unsigned long long>;
using tran_query_res = std::pair<transaction::status, std::vector<transaction_t>>;

#endif //UCU_BANK_TRANSACTION_CONSTANTS_HPP
