#include "account/client.h"

namespace account {
    account::status Client::create(const std::string &user_id, const std::string &account_type) {
        return ver_connection(
            [&, this](){ return client->call(method::CREATE, user_id, account_type).as<account::status>(); }
        );
    }

    std::pair<account::status, account_t> Client::get(const std::string &card, const auth::AuthDU &ctrl) {
        return ver_connection(
            [&, this](){ return client->call(method::GET, card, ctrl).as<std::pair<account::status, account_t>>(); }
        );
    }

    account::status Client::remove(const std::string &card, const auth::AuthDU &ctrl) {
        return ver_connection(
            [&, this]() { return client->call(method::REMOVE, card, ctrl).as<account::status>(); }
        );
    }

    account::status Client::transaction(const std::string &from, const std::string &to, double amount) {
        return ver_connection(
            [&, this]() { return client->call(method::TRANSACTION, from, to, amount).as<account::status>(); }
        );
    }

    account::status Client::exists(const std::string &card) {
        return ver_connection(
            [&, this]() { return client->call(method::EXISTS, card).as<account::status>(); }
        );
    }

    std::pair<account::status, std::vector<account_t>> Client::get_all(const std::string &user_id, const auth::AuthDU &ctrl) {
        return ver_connection(
            [&, this]() { return client->call(method::GET_ALL, user_id, ctrl).as<std::pair<account::status, std::vector<account_t>>>(); }
        );
    }
}
