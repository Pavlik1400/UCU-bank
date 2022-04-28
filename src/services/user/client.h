#ifndef UCU_BANK_USER_CLIENT_H
#define UCU_BANK_USER_CLIENT_H

#include <rpc/client.h>
#include <rpc/config.h>
#include "user/constants.h"
#include "client/client.hpp"

namespace user {
    class Client: public client::BasicClient {
    public:
        Client(std::string &&addr, int port)
            : client::BasicClient(std::move(addr)
                , port
                , "USER"
            ) {};

        explicit Client(std::string &&addr)
            : client::BasicClient(std::move(addr)
                , rpc::constants::DEFAULT_PORT
                , "USER"
            ) {};

        status create(const user_t &user);

        std::pair<status, user_t> get(const std::string &phoneNo);

        status remove(const std::string &phoneNo);

        status exists(const std::string &phoneNo);

        status valid_id(const std::string &id);
    };
}


#endif //UCU_BANK_USER_CLIENT_H
