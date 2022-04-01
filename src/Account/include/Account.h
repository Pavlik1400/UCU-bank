#ifndef UCU_BANK_ACCOUNT_H
#define UCU_BANK_ACCOUNT_H

#include <iostream>
#include <string>

//class Account {
//public:
//    inline static const std::string ID = "_id";
//    inline static const std::string USER_ID = "userId";
//    inline static const std::string NUMBER = "number";
//    inline static const std::string TYPE = "type_";
//    inline static const std::string INTEREST_RATE = "interestRate";
//    inline static const std::string OPENING_DATE = "openingDate";
//    inline static const std::string ACTIVE = "active";
//    inline static const std::string BALANCE = "balance";
//
//    size_t id;
//    size_t userId;
//    std::string number;
//    AccountType type;
//    double interestRate;
//    std::string openingDate;
//    bool active;
//    std::string card;
//    double balance;
//};

namespace Account {
    const std::string ID = "_id";
    const std::string USER_ID = "userId";
    const std::string CVV = "cvv";
    const std::string NUMBER = "number";
    const std::string TYPE = "type_";
    const std::string OPENING_DATE = "openingDate";
    const std::string ACTIVE = "active";
    const std::string BALANCE = "balance";
}


#endif //UCU_BANK_ACCOUNT_H
