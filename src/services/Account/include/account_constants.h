#ifndef UCU_BANK_ACCOUNT_CONSTANTS_H
#define UCU_BANK_ACCOUNT_CONSTANTS_H
#include <string>

namespace response {
    const std::string STATUS = "status";
    enum type {
        OK,
        FAILED,
        EXISTS,
        NO_EXISTS,
        BAD_TYPE
    };
    const std::string INSTANCE = "instance";
}

namespace request {
    const std::string TYPE = "type";
    enum type {
        CREATE,
        GET,
        UPDATE,
        REMOVE,
        TRANSACTION,
        EXISTS,
        CREATE_WITHOUT_CHECK
    };
}

typedef struct {
    int status;
} status_t;


#endif //UCU_BANK_ACCOUNT_CONSTANTS_H
