#include "AccountMicroservice.h"
#include "constants.hpp"

void AccountMicroservice::custom_start() {
    db = client["users"];
    users = db["users"];
    wc_majority.acknowledge_level(mongocxx::write_concern::level::k_majority);
    rc_local.acknowledge_level(mongocxx::read_concern::level::k_local);
    rp_primary.mode(mongocxx::read_preference::read_mode::k_primary);
    sopts.write_concern(wc_majority);
    sopts.read_concern(rc_local);
    sopts.read_preference(rp_primary);
}

void AccountMicroservice::receive_callback(const nlohmann::json &msg) {
    auto type = msg["type"].get<int>();
    (this->*selector[type])(msg);
}

void AccountMicroservice::create(const nlohmann::json &msg) {
    auto doc = document{}
            << Account::ID << msg[Account::ID].get<ssize_t>()
            << Account::USER_ID << msg[Account::USER_ID].get<ssize_t>()
            << Account::NUMBER << msg[Account::NUMBER].get<ssize_t>()
            << Account::TYPE << msg[Account::TYPE].get<int>()
            << Account::INTEREST_RATE << msg[Account::INTEREST_RATE].get<double>()
            << Account::OPENING_DATE << msg[Account::OPENING_DATE].get<std::string>()
            << Account::ACTIVE << msg[Account::ACTIVE].get<bool>()
            << Account::BALANCE << msg[Account::BALANCE].get<double>()
            << finalize;
    auto status = users.insert_one(session, doc.view());
    nlohmann::json response;
    response[constants::MESSAGE_KEY_DST] = msg[constants::MESSAGE_KEY_DST];
    response[constants::MESSAGE_KEY_UUID] = msg[constants::MESSAGE_KEY_UUID];
    if (status) {
        response[response::STATUS] = response::type::OK;
    } else {
        response[response::STATUS] = response::type::EXISTS;
    }
    BasicMicroservice::send_response(response);
}

void AccountMicroservice::get(const nlohmann::json &msg) {

}

void AccountMicroservice::update(const nlohmann::json &msg) {

}

void AccountMicroservice::remove(const nlohmann::json &msg) {

}

