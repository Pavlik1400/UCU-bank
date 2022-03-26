#ifndef UCU_BANK_ACCOUNT_H
#define UCU_BANK_ACCOUNT_H

#include <iostream>
#include <string>
#include "AccountType.h"

class Account {
    size_t id;
    std::string number;
    AccountType type;
    double interestRate;
    std::string openingDate;
    bool active;
    std::string card;
    double balance;
};


#endif //UCU_BANK_ACCOUNT_H
