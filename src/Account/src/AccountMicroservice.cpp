#include "AccountMicroservice.h"
#include "constants.hpp"
#include "utils.h"

void AccountMicroservice::custom_start() {
    db = client["users"];
    users = db["users"];
    users.create_index(session, document{} << Account::USER_ID << 1 << finalize);
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

/**
 * Inner method that will be called after verification of USER_ID
 * @param msg
 * Expects:
 * msg[USER_ID]: std::string
 * msg[TYPE]: int
 */
void AccountMicroservice::create_without_check(const nlohmann::json &msg) {

    auto user_id = msg[Account::USER_ID].get<std::string>();
    auto account_type = msg[Account::TYPE].get<int>();
    auto card = generate_card_token();

    // generate unique card number
    while (users.find_one(session, document{} << Account::NUMBER << card << finalize)) {
        card = generate_card_token();
    }

    auto doc = document{} << Account::USER_ID << user_id << Account::NUMBER << card << Account::CVV << generate_cvv()
                          << Account::TYPE << account_type << Account::OPENING_DATE << generate_current_datetime()
                          << Account::ACTIVE << true << Account::BALANCE << 0.0 << finalize;
    auto status = users.insert_one(session, doc.view());
    nlohmann::json response;
    response[constants::MESSAGE_KEY_DST] = msg[constants::MESSAGE_KEY_DST];
    response[constants::MESSAGE_KEY_UUID] = msg[constants::MESSAGE_KEY_UUID];

    if (status) {
        response[response::STATUS] = response::type::OK;
    } else {
        response[response::STATUS] = response::type::EXISTS;
    }
    send_response(response);
}

void AccountMicroservice::create(const nlohmann::json &msg) {
    create_without_check(msg); // Temporary
}

void AccountMicroservice::get(const nlohmann::json &msg) {

}

void AccountMicroservice::update(const nlohmann::json &msg) {

}

void AccountMicroservice::remove(const nlohmann::json &msg) {

}

/**
 *
 * @param msg
 * Expects:
 * msg[FROM]: std::string
 * msg[TO]: std::string
 * msg[AMOUNT]: double
 */
void AccountMicroservice::transaction(const nlohmann::json &msg) {
    auto from = msg["FROM"].get<std::string>();
    auto to = msg["TO"].get<std::string>();
    auto amount = msg["AMOUNT"].get<double>();
    auto status1 = users.update_one(session, document{} << Account::NUMBER << from << finalize,
                                    document{} << INC << open_document << Account::BALANCE << -1 * amount
                                               << close_document << finalize);
    auto status2 = users.update_one(session, document{} << Account::NUMBER << to << finalize,
                                    document{} << INC << open_document << Account::BALANCE << amount << close_document
                                               << finalize);

    nlohmann::json response;
    response[constants::MESSAGE_KEY_DST] = msg[constants::MESSAGE_KEY_DST];
    response[constants::MESSAGE_KEY_UUID] = msg[constants::MESSAGE_KEY_UUID];
    response[response::STATUS] = (status1 && status2) ? response::type::OK : response::type::FAILED;
    send_response(response);
}

/**
 *
 * @param msg
 * Expects:
 * msg[NUMBER]: std::string
 */
void AccountMicroservice::exists(const nlohmann::json &msg) {
    auto status = users.find_one(session,
                                 document{} << Account::NUMBER << msg[Account::NUMBER].get<std::string>() << finalize);
    nlohmann::json response;
    response[constants::MESSAGE_KEY_DST] = msg[constants::MESSAGE_KEY_DST];
    response[constants::MESSAGE_KEY_UUID] = msg[constants::MESSAGE_KEY_UUID];
    response[response::STATUS] = status ? response::type::EXISTS : response::type::NO_EXISTS;
    send_response(response);

}

