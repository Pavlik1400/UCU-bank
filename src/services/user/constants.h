#ifndef UCU_BANK_USER_CONSTANTS_H
#define UCU_BANK_USER_CONSTANTS_H

#include <iostream>
#include <string>
#include <rpc/msgpack.hpp>

namespace user {

    const std::string ID = "_id";
    const std::string TYPE = "type";
    const std::string NAME = "name";
    const std::string PASSWORD = "password";
    const std::string DATE_OF_BIRTH = "dateOfBirth";
    const std::string PHONE_NO = "phoneNo";
    const std::string EMAIL = "email";
    const std::string ADDRESS = "address";
    const std::string GENDER = "gender";
    const std::string JOINING_DATE = "joiningDate";

    enum status {
        OK = 0,
        INCOMPLETE_USER_IDENTITY = 1,
        CREATION_FAILED = 2,
        MISSING_PASSWORD = 3,
        GET_FAILED = 4,
        USER_EXISTS = 5,
        USER_DOESNT_EXIST = 6,
        INVALID_USER_ID = 7
    };

    inline std::string status_to_str(status s) {
        switch (s) {
            case OK: return "OK";
            case INCOMPLETE_USER_IDENTITY: return "INCOMPLETE_USER_IDENTITY";
            case CREATION_FAILED: return "CREATION_FAILED";
            case MISSING_PASSWORD: return "MISSING_PASSWORD";
            case GET_FAILED: return "GET_FAILED";
            case USER_EXISTS: return "USER_EXISTS";
            case USER_DOESNT_EXIST: return "USER_DOESNT_EXIST";
            default: return "DB ERROR";
        }
    }
}

MSGPACK_ADD_ENUM(user::status)

struct user_t {
    std::string id;
    std::string type;
    std::string name;
    std::string password;
    std::string date_of_birth;
    std::string phoneNo;
    std::string email;
    std::string address;
    std::string gender;
    std::string joining_date;
    MSGPACK_DEFINE (id, type, name, password, date_of_birth, phoneNo, email, address, gender, joining_date);
};

inline std::ostream &operator<<(std::ostream &os, const user_t &account) {
    os << "{\n" << "}\n";
    return os;
}

#endif //UCU_BANK_USER_CONSTANTS_H
