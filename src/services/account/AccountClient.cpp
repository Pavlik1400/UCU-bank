#include "account/AccountClient.h"


account::status AccountClient::create(const std::string &user_id, const std::string &account_type) {
    return client.call("create", user_id, account_type).as<account::status>();
}


std::pair<account::status, account_t> AccountClient::get(const std::string &card) {
    return client.call("get", card).as<std::pair<account::status, account_t>>();
}

account::status AccountClient::remove(const std::string &card) {
    return client.call("remove", card).as<account::status>();
}

account::status AccountClient::transaction(const std::string &from, const std::string &to, double amount) {
    return client.call("transaction", from, to, amount).as<account::status>();
}


account::status AccountClient::exists(const std::string &card) {
    return client.call("exists", card).as<account::status>();
}
