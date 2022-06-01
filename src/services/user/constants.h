#ifndef UCU_BANK_USER_CONSTANTS_H
#define UCU_BANK_USER_CONSTANTS_H

#include <iostream>
#include <string>
#include <rpc/msgpack.hpp>

namespace user {

    namespace method {
        const std::string CREATE = "create";
        const std::string REMOVE = "remove";
        const std::string GET_BY_UID = "get_by_uid";
        const std::string GET_BY_EMAIL= "get_by_email";
        const std::string GET_BY_PHONE_NO= "get_by_phone_no";
        const std::string EXISTS= "exists";
        const std::string VALID_ID= "valid_id";
        const std::string VALID_PASSWORD= "valid_password";
    }

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

    namespace password {
        const std::string SALT = "salt";
    }

    enum status {
        OK = 0,
        INCOMPLETE_USER_IDENTITY = 1,
        CREATION_FAILED = 2,
        MISSING_PASSWORD = 3,
        GET_FAILED = 4,
        USER_EXISTS = 5,
        USER_DOESNT_EXIST = 6,
        INVALID_USER_ID = 7,
        INVALID_PASSWORD = 8,
    };
    namespace {
        enum by {
            ID = 0,
            PHONE_NO = 1,
            EMAIL = 2,

        };
    }


    inline std::string status_to_str(status s) {
        switch (s) {
            case OK: return "OK";
            case INCOMPLETE_USER_IDENTITY: return "INCOMPLETE_USER_IDENTITY";
            case CREATION_FAILED: return "CREATION_FAILED";
            case MISSING_PASSWORD: return "MISSING_PASSWORD";
            case GET_FAILED: return "GET_FAILED";
            case USER_EXISTS: return "USER_EXISTS";
            case USER_DOESNT_EXIST: return "USER_DOESNT_EXIST";
            case INVALID_PASSWORD: return "INVALID_PASSWORD";
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
    MSGPACK_DEFINE(id, type, name, password, date_of_birth, phoneNo, email, address, gender, joining_date);
};

inline std::ostream &operator<<(std::ostream &os, const user_t &account) {
    os << "{\n" << "}\n";
    return os;
}

#endif //UCU_BANK_USER_CONSTANTS_H
