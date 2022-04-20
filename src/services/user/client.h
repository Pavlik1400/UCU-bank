#ifndef UCU_BANK_USER_CLIENT_H
#define UCU_BANK_USER_CLIENT_H

#include <rpc/client.h>
#include "user/constants.h"

namespace user {
    class Client {
    private:
        rpc::client client;
    public:
        Client(const std::string &addr, int port) : client(addr, port) {};

        explicit Client(const std::string &addr) : client(addr, rpc::constants::DEFAULT_PORT) {};

        status create(const user_t &user);

        std::pair<status, user_t> get(const std::string &phoneNo);

        status remove(const std::string &phoneNo);

        status exists(const std::string &phoneNo);

        status valid_id(const std::string &id);
    };
}


#endif //UCU_BANK_USER_CLIENT_H
