#ifndef UCU_BANK_CREDIT_SERVICE_CONSTANTS_H
#define UCU_BANK_CREDIT_SERVICE_CONSTANTS_H

#include <string>
#include <rpc/msgpack.hpp>

namespace credit {
    const std::string ID = "credit_id";
    const std::string USER_ID = "userId";
    const std::string CARD_NUMBER = "cardNumber";
    const std::string OPENING_DATE = "openingDate";
    const std::string ACTIVE = "active";
    const std::string ORIGINAL_BALANCE = "originalBalance";
    const std::string CURRENT_BALANCE = "currentBalance";
    const std::string PERCENT = "percent";
    const std::string PERIOD = "period";

    namespace method {
        const std::string CREATE = "create";
        const std::string GET_ALL = "get_all";
        const std::string FINISH_CREDIT = "finish_credit";
    }

    enum status {
        OK = 0,
        INVALID_USER_ID = 1,
        CREATION_FAILED = 2,
        INVALID_CARD_NUMBER = 3,
        GET_FAILED = 4,
        TRANSACTION_FAILED = 5,
        NOT_ENOUGH_PRIVILEGES = 6,
        INVALID_ACCOUNT_ID = 7,
        NOT_ENOUGH_MONEY = 8,
    };

    inline std::string status_to_str(status s) {
        switch(s) {
            case OK: return "OK";
            case INVALID_USER_ID: return "INVALID_USER_ID";
            case CREATION_FAILED: return "CREATION_FAILED";
            case INVALID_CARD_NUMBER: return "INVALID_CARD_NUMBER";
            case GET_FAILED: return "GET_FAILED";
            case TRANSACTION_FAILED: return "TRANSACTION_FAILED";
            case NOT_ENOUGH_PRIVILEGES: return "NOT_ENOUGH_PRIVILEGES";
            case INVALID_ACCOUNT_ID: return "INVALID_ACCOUNT_ID";
            case NOT_ENOUGH_MONEY: return "NOT_ENOUGH_MONEY";
            default: return "DB ERROR";
        }
    }

    const std::vector<std::pair<int, double>> CREDIT_TYPES = { // period, percent
            {3, 7.2},
            {6, 5.5},
            {12, 3.5},
    };

}

MSGPACK_ADD_ENUM(credit::status)


struct credit_t {
    std::string id;
    std::string user_id;
    std::string card_number;
    std::string opening_date;
    bool active;
    double original_balance;
    double current_balance;
    double percent;
    int period;
    MSGPACK_DEFINE (id, user_id, card_number, opening_date, active, original_balance, current_balance, percent, period);
};


inline std::ostream &operator<<(std::ostream &os, const credit_t &credit_) {
    os << "{\n\t" << credit::ID << ": " << credit_.id << "\n\t"
                  << credit::USER_ID << ": " << credit_.user_id << "\n\t"
                  << credit::CARD_NUMBER << ": " << credit_.card_number << "\n\t"
                  << credit::OPENING_DATE << ": " << credit_.opening_date << "\n\t"
                  << credit::ACTIVE << ": " << credit_.active << "\n\t"
                  << credit::ORIGINAL_BALANCE << ": " << credit_.original_balance << "\n\t"
                  << credit::ORIGINAL_BALANCE << ": " << credit_.current_balance << "\n\t"
                  << credit::PERCENT << ": " << credit_.percent << "\n\t"
                  << credit::PERIOD << ": " << credit_.period << "\n\t"
       << "}\n";
    return os;
}


#endif //UCU_BANK_CREDIT_SERVICE_CONSTANTS_H
