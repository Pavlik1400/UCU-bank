#ifndef UCU_BANK_USERCLIENT_H
#define UCU_BANK_USERCLIENT_H
#include <rpc/client.h>
#include "user_constants.h"

class UserClient {
private:
    rpc::client client;
public:
    UserClient(const std::string &addr, int port): client(addr, port) {};
    UserClient(const std::string &addr): UserClient(addr, rpc::constants::DEFAULT_PORT) {};

    user::status create(const user_t &user);

    std::pair<user::status, user_t> get(const std::string &name, const std::string &phoneNo);

    user::status remove(const std::string &name, const std::string &phoneNo);

    user::status exists(const std::string &name, const std::string &phoneNo);

    user::status valid_id(const std::string &id);


};

#endif //UCU_BANK_USERCLIENT_H
