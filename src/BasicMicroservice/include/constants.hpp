#ifndef UCU_BANK_CONSTANTS_HPP
#define UCU_BANK_CONSTANTS_HPP

#include <string>

namespace constants {
    const std::string MESSAGE_KEY_DST = "dst";
    const std::string MESSAGE_KEY_UUID = "uuid";

    const std::string MESSAGE_KEY_TYPE = "msg_type";
    namespace message_types {
        const std::string REQUEST = "request";
        const std::string RESPONSE = "response";
    }

    const std::string MESSAGE_KEY_TIMESTAMP = "timestamp";
}

#endif //UCU_BANK_CONSTANTS_HPP
