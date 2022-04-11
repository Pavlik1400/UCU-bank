#ifndef UCU_BANK_ACCOUNT_CONSTANTS_H
#define UCU_BANK_ACCOUNT_CONSTANTS_H

#include <iostream>
#include <string>
#include <rpc/msgpack.hpp>

namespace account {
    const std::string ID = "_id";
    const std::string USER_ID = "userId";
    const std::string CVV = "cvv";
    const std::string NUMBER = "number";
    const std::string TYPE = "type";
    const std::string OPENING_DATE = "openingDate";
    const std::string ACTIVE = "active";
    const std::string BALANCE = "balance";

    enum status {
        OK = 0,
        INVALID_USER_ID = 1,
        CREATION_FAILED = 2,
        INVALID_CARD_NUMBER = 3,
        GET_FAILED = 4,
        TRANSACTION_FAILED = 5,
    };
}

MSGPACK_ADD_ENUM(account::status)

struct account_t {
    std::string id;
    std::string user_id;
    std::string cvv;
    std::string number;
    std::string type;
    std::string opening_date;
    bool active;
    double balance;
    MSGPACK_DEFINE (id, user_id, cvv, number, type, opening_date, active, balance);
};

inline std::ostream &operator<<(std::ostream &os, const account_t &account) {
    os << "{\n" << account::USER_ID << " : " << account.user_id << '\n' << account::CVV << " : " << account.cvv << '\n'
       << account::NUMBER << " : " << account.number << '\n' << account::TYPE << " : " << account.type << '\n'
       << account::OPENING_DATE << " : " << account.opening_date << '\n' << account::ACTIVE << " : " << account.active
       << '\n' << account::BALANCE << " : " << account.balance << "\n}\n";
    return os;
}

#endif //UCU_BANK_ACCOUNT_CONSTANTS_H
