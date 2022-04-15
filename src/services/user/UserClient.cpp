#include "user/UserClient.h"

user::status UserClient::create(const user_t &user) {
    return client.call("create", user).as<user::status>();
}

std::pair<user::status, user_t> UserClient::get(const std::string &name, const std::string &phoneNo) {
    return client.call("get", name, phoneNo).as<std::pair<user::status, user_t>>();
}

user::status UserClient::remove(const std::string &name, const std::string &phoneNo) {
    return client.call("remove", name, phoneNo).as<user::status>();
}

user::status UserClient::exists(const std::string &name, const std::string &phoneNo) {
    return client.call("exists", name, phoneNo).as<user::status>();
}

user::status UserClient::valid_id(const std::string &id) {
    return client.call("valid_id", id).as<user::status>();
}
