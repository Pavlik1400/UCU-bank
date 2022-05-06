#include "client.h"

namespace user {
    status Client::create(const user_t &user) {
        return ver_connection([&, this]() { return client->call("create", user).as<status>(); });
    }

    std::pair<status, user_t> Client::get(const std::string &phoneNo) {
        return ver_connection([&, this]() { return client->call("get", phoneNo).as<std::pair<status, user_t>>(); });
    }

    status Client::remove(const std::string &phoneNo) {
        return ver_connection([&, this]() { return client->call("remove", phoneNo).as<status>(); });
    }

    status Client::exists(const std::string &phoneNo) {
        return ver_connection([&, this]() { return client->call("exists", phoneNo).as<status>(); });
    }

    status Client::valid_id(const std::string &id) {
        return ver_connection([&, this]() { return client->call("valid_id", id).as<status>(); });
    }

    status Client::valid_password(const std::string &phoneNo, const std::string &password) {
        return ver_connection([&, this]() { return client->call("valid_password", phoneNo, password).as<status>(); });
    }
}
