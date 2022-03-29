#ifndef UCU_BANK_CONSTANTS_H
#define UCU_BANK_CONSTANTS_H
//namespace {
//    enum AccountRequests {
//        CREATE,
//        GET,
//        UPDATE,
//        REMOVE
//    };
//
//    enum AccountResponseStatus {
//        OK,
//        EXISTS,
//        BAD_TYPE
//    };
//}

#include <string>

namespace response {
    const std::string STATUS = "status";
    enum type {
        OK,
        EXISTS,
        BAD_TYPE
    };
}

namespace request {
    const std::string TYPE = "type";
    enum type {
        CREATE,
        GET,
        UPDATE,
        REMOVE
    };
}


#endif //UCU_BANK_CONSTANTS_H
