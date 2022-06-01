#ifndef UCU_BANK_ACCOUNT_CLIENT_H
#define UCU_BANK_ACCOUNT_CLIENT_H

//#include <rpc/client.h>
#include "account/constants.h"
#include "client/client.hpp"

namespace account {
    class Client: public client::BasicClient{
    public:
        Client(std::string &&addr, int port)
            : client::BasicClient(
                std::move(addr),
                port,
                "ACCOUNT"
            ) {};

        explicit Client(std::string &&addr)
            : client::BasicClient(
                std::move(addr),
                rpc::constants::DEFAULT_PORT,
                "ACCOUNT"
            ) {}

        account::status create(const std::string &user_id, const std::string &account_type);

        std::pair<account::status, account_t> get(const std::string &card);

        account::status remove(const std::string &card);

        account::status transaction(const std::string &from, const std::string &to, double amount);

        account::status exists(const std::string &card);

        std::pair<account::status, std::vector<account_t>> get_all(const std::string &user_id);
    };
}


#endif //UCU_BANK_ACCOUNT_CLIENT_H
