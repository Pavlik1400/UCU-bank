#include "credit/client.h"

namespace credit {
    credit::status Client::create(const std::string &user_id, const std::string &card, int credit_type, double balance, const auth::AuthDU &ctrl) {
        return ver_connection(
                [&, this](){ return client->call(method::CREATE, user_id, card, credit_type, balance, ctrl).as<credit::status>(); }
        );
    }

    std::pair<credit::status, std::vector<credit_t>> Client::get_all(const std::string &user_id, const auth::AuthDU &ctrl) {
        return ver_connection(
                [&, this]() { return client->call(method::GET_ALL, user_id, ctrl).as<std::pair<credit::status, std::vector<credit_t>>>(); }
        );
    }

    credit::status Client::finish_credit(const std::string &user_id, const std::string &credit_id, const auth::AuthDU &ctrl) {
        return ver_connection(
                [&, this](){ return client->call(method::FINISH_CREDIT, user_id, credit_id, ctrl).as<credit::status>(); }
        );
    }

}
