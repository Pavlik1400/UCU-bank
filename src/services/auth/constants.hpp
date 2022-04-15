#ifndef UCU_BANK_AUTH_CONSTANTS_H
#define UCU_BANK_AUTH_CONSTANTS_H

#include <iostream>
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
}

MSGPACK_ADD_ENUM(auth::status)

#endif //UCU_BANK_AUTH_CONSTANTS_H