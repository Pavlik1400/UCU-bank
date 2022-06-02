#include "client.h"

namespace user {
    status Client::create(const user_t &user) {
        return ver_connection([&, this]() { return client->call(method::CREATE, user).as<status>(); });
    }

    status Client::remove(const std::string &phoneNo, const auth::AuthDU &ctrl) {
        return ver_connection([&, this]() { return client->call(method::REMOVE, phoneNo, ctrl).as<status>(); });
    }

    status Client::exists(const std::string &phoneNo) {
        return ver_connection([&, this]() { return client->call(method::EXISTS, phoneNo).as<status>(); });
    }

    status Client::valid_id(const std::string &id) {
        return ver_connection([&, this]() { return client->call(method::VALID_ID, id).as<status>(); });
    }

    status Client::valid_password(const std::string &phoneNo, const std::string &password) {
        return ver_connection(
                [&, this]() { return client->call(method::VALID_PASSWORD, phoneNo, password).as<status>(); });
    }
}
