#ifndef UCU_BANK_ACCOUNT_CLIENT_H
#define UCU_BANK_ACCOUNT_CLIENT_H

#include <rpc/client.h>
#include "account/constants.h"

namespace account {
    class Client {
    private:
        rpc::client client;
    public:
        Client(const std::string &addr, int port) : client(addr, port) {};

        explicit Client(const std::string &addr) : Client(addr, rpc::constants::DEFAULT_PORT) {};

        account::status create(const std::string &user_id, const std::string &account_type);

        std::pair<account::status, account_t> get(const std::string &card);

        account::status remove(const std::string &card);

        account::status transaction(const std::string &from, const std::string &to, double amount);

        account::status exists(const std::string &card);

        std::pair<account::status, std::vector<account_t>> get_all(const std::string &user_id)
    };
}


#endif //UCU_BANK_ACCOUNT_CLIENT_H
