#ifndef UCU_BANK_USER_CLIENT_H
#define UCU_BANK_USER_CLIENT_H

//#include <rpc/client.h>
//#include <rpc/config.h>
#include "user/constants.h"
#include "client/client.hpp"

namespace user {
    class Client : public client::BasicClient {
    public:
        Client(std::string &&addr, int port) : client::BasicClient(std::move(addr), port, "USER") {};

        explicit Client(std::string &&addr) : client::BasicClient(std::move(addr), rpc::constants::DEFAULT_PORT,
                                                                  "USER") {};

        status create(const user_t &user);

        template<by filter>
        std::pair<status, user_t> get(const std::string &identifier);

        status remove(const std::string &phoneNo);

        status exists(const std::string &phoneNo);

        status valid_id(const std::string &id);

        status valid_password(const std::string &phoneNo, const std::string &password);
    };

    template<by filter>
    constexpr auto map_to_method() {
        switch (filter) {
            case by::ID:
                return method::GET_BY_UID;
            case by::EMAIL:
                return method::GET_BY_EMAIL;
            case by::PHONE_NO:
                return method::GET_BY_PHONE_NO;
        }
    }

    template<by filter>
    std::pair<status, user_t> Client::get(const std::string &identifier) {
        return ver_connection([&, this]() {
            return client->call(map_to_method<filter>(), identifier).template as<std::pair<status, user_t>>();
        });
    }
}


#endif //UCU_BANK_USER_CLIENT_H
