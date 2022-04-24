#include "account/client.h"

namespace account {
    account::status Client::create(const std::string &user_id, const std::string &account_type) {
        return client.call("create", user_id, account_type).as<account::status>();
    }

    std::pair<account::status, account_t> Client::get(const std::string &card) {
        return client.call("get", card).as<std::pair<account::status, account_t>>();
    }

    account::status Client::remove(const std::string &card) {
        return client.call("remove", card).as<account::status>();
    }

    account::status Client::transaction(const std::string &from, const std::string &to, double amount) {
        return client.call("transaction", from, to, amount).as<account::status>();
    }

    account::status Client::exists(const std::string &card) {
        return client.call("exists", card).as<account::status>();
    }

    std::pair<account::status, std::vector<account_t>> Client::get_all(const std::string &user_id) {
        return client.call("get_all", user_id).as<std::pair<account::status, std::vector<account_t>>>();
    }
}
