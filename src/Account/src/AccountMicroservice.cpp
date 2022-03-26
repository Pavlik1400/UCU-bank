#include "AccountMicroservice.h"

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

}

void AccountMicroservice::get(const nlohmann::json &msg) {

}

void AccountMicroservice::update(const nlohmann::json &msg) {

}

void AccountMicroservice::remove(const nlohmann::json &msg) {

}

