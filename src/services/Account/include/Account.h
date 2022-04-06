#ifndef UCU_BANK_ACCOUNT_H
#define UCU_BANK_ACCOUNT_H

#include <iostream>
#include <string>
#include <msgpack.hpp>

namespace Account {
    const std::string ID = "_id";
    const std::string USER_ID = "userId";
    const std::string CVV = "cvv";
    const std::string NUMBER = "number";
    const std::string TYPE = "type";
    const std::string OPENING_DATE = "openingDate";
    const std::string ACTIVE = "active";
    const std::string BALANCE = "balance";
}

typedef struct account_t {
    std::string id;
    std::string user_id;
    std::string cvv;
    std::string number;
    std::string type;
    std::string opening_date;
    bool active;
    double balance;
    MSGPACK_DEFINE(id, user_id, cvv, number, type, opening_date, active, balance);
} account_t;
#endif //UCU_BANK_ACCOUNT_H
