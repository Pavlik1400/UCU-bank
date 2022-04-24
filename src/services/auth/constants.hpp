#ifndef UCU_BANK_AUTH_CONSTANTS_H
#define UCU_BANK_AUTH_CONSTANTS_H

#include <iostream>
#include <sstream>
#include <string>
#include <rpc/msgpack.hpp>

namespace auth {
    enum status {
        OK = 0,
        INVALID_NAME_OR_PHONE = 1,
        INVALID_DB_RESPONSE = 2,
        INVALID_USER_PASSWORD = 3,

        CREATION_FAILED = 4,
        INVALID_CARD_NUMBER = 5,
        GET_FAILED = 6,
        TRANSACTION_FAILED = 7,
        RPC_FAILED = 8,
        HASH_FAILED = 9,
        MAIL_FAILED = 10
    };

    inline std::string status_to_str(status s) {
        switch (s) {
            case OK: return "OK";
            case INVALID_NAME_OR_PHONE: return "INVALID_NAME_OR_PHONE";
            case INVALID_DB_RESPONSE: return "INVALID_DB_RESPONSE";
            case INVALID_USER_PASSWORD: return "INVALID_USER_PASSWORD";
            case CREATION_FAILED: return "CREATION_FAILED";
            case INVALID_CARD_NUMBER: return "INVALID_CARD_NUMBER";
            case GET_FAILED: return "GET_FAILED";
            case TRANSACTION_FAILED: return "TRANSACTION_FAILED";
            case RPC_FAILED: return "RPC_FAILED";
            case HASH_FAILED: return "HASH_FAILED";
            case MAIL_FAILED: return "MAIL_FAILED";
            default: return "UMKNOWN ERROR";
        }
    }

    inline std::ostream &operator<<(std::ostream &os, const status &s)
    {
        return os << std::string{"auth::status::"+status_to_str(s)};
    }
    
    struct AuthDU {
        std::string cred;
        std::string data;
        MSGPACK_DEFINE (cred, data);
    };
}

MSGPACK_ADD_ENUM(auth::status)

#endif //UCU_BANK_AUTH_CONSTANTS_H