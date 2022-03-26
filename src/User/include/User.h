#ifndef UCU_BANK_ACCOUNT_H
#define UCU_BANK_ACCOUNT_H

#include <iostream>
#include <string>
#include "UserType.h"

class User {
    size_t id;
    UserType type;
    std::string name;
    std::string password;
    std::string dateOfBirth;
    std::string phoneNo;
    std::string emailId;
    std::string address;
    std::string gender;
    std::string joiningDate;
};


#endif //UCU_BANK_ACCOUNT_H
