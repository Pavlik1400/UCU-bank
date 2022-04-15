#ifndef UCU_BANK_ACCOUNTCLIENT_H
#define UCU_BANK_ACCOUNTCLIENT_H
#include <rpc/client.h>
#include "account/account_constants.h"

class AccountClient {
private:
    rpc::client client;
public:
    AccountClient(const std::string &addr, int port): client(addr, port) {};
    AccountClient(const std::string &addr): AccountClient(addr, rpc::constants::DEFAULT_PORT) {};

    account::status create(const std::string &user_id, const std::string &account_type);

    std::pair<account::status, account_t> get(const std::string &card);

    account::status remove(const std::string &card);

    account::status transaction(const std::string &from, const std::string &to, double amount);

    account::status exists(const std::string &card);
};

#endif //UCU_BANK_ACCOUNTCLIENT_H
