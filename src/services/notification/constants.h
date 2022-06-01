#ifndef UCU_BANK_NOTIFICATION_CONSTANTS_H
#define UCU_BANK_NOTIFICATION_CONSTANTS_H
#include <string>
#include <rpc/msgpack.hpp>

namespace notification {
    const char email_sep=':';



}

enum identifier_type {
    EMAIL = 0,
    USER_ID = 1,
    CARD_NUMBER = 2,
    PHONE_NO = 3
};

MSGPACK_ADD_ENUM(identifier_type)

struct notification_t {
    std::string identifier{};
    std::string payload{};
    identifier_type type{};
    MSGPACK_DEFINE(identifier, payload, type);

};

#endif //UCU_BANK_NOTIFICATION_CONSTANTS_H
