#ifndef UCU_BANK_CREDIT_CLIENT_H
#define UCU_BANK_CREDIT_CLIENT_H

#include "credit/constants.h"
#include "auth/constants.hpp"
#include "client/client.hpp"


namespace credit {
    class Client : public client::BasicClient {
    public:
        Client(std::string &&addr, int port) : client::BasicClient(std::move(addr), port, "CREDIT") {};

        explicit Client(std::string &&addr) : client::BasicClient(std::move(addr), rpc::constants::DEFAULT_PORT,
                                                                  "CREDIT") {};

        credit::status create(const std::string &user_id, const std::string &card, int credit_type, double balance, const auth::AuthDU &ctrl);

        std::pair<credit::status, std::vector<credit_t>> get_all(const std::string &user_id, const auth::AuthDU &ctrl);

        credit::status finish_credit(const std::string &user_id, const std::string &credit_id, const auth::AuthDU &ctrl);
    };

}


#endif //UCU_BANK_CREDIT_CLIENT_H
