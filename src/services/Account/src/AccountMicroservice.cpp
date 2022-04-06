#include "AccountMicroservice.h"
#include "constants.hpp"
#include "utils.h"

void AccountMicroservice::start() {
    db = client["users"];
    users = db["users"];
    users.create_index(session, document{} << Account::USER_ID << 1 << finalize);
    users.create_index(session, document{} << Account::NUMBER << 1 << finalize);
    wc_majority.acknowledge_level(mongocxx::write_concern::level::k_majority);
    rc_local.acknowledge_level(mongocxx::read_concern::level::k_local);
    rp_primary.mode(mongocxx::read_preference::read_mode::k_primary);
    sopts.write_concern(wc_majority);
    sopts.read_concern(rc_local);
    sopts.read_preference(rp_primary);
}


/**
 * Inner method that will be called after verification of USER_ID
 * @param msg
 * Expects:
 * msg[USER_ID]: std::string
 * msg[TYPE]: int
 */
status_t AccountMicroservice::create(const std::string &user_id, const std::string &account_type) {
    auto card = generate_card_token();

    // generate unique card number
    while (users.find_one(session, document{} << Account::NUMBER << card << finalize)) {
        card = generate_card_token();
    }
    std::cout << card << std::endl;
    std::cout << generate_cvv() << std::endl;
    auto doc = document{} << Account::USER_ID << user_id << Account::NUMBER << card << Account::CVV << generate_cvv()
                          << Account::TYPE << account_type << Account::OPENING_DATE << generate_current_datetime()
                          << Account::ACTIVE << true << Account::BALANCE << 0.0 << finalize;
    auto status = users.insert_one(session, doc.view());

    return {(status ? response::type::OK : response::type::EXISTS)};
}


/**
 * @param msg
 * Expects:
 * msg[NUMBER]: std::string
 */
account_t AccountMicroservice::get(const std::string &card) {
    bsoncxx::stdx::optional<bsoncxx::document::value> result = users.find_one(session,
                                                                              document{} << Account::NUMBER << card
                                                                                         << finalize);
    account_t account;
    if (result) {
//        account.user_id = (*result)[Account::ID].get;
    }
//    } else {
//        response[response::STATUS] = response::type::NO_EXISTS;
//    }
//
//    send_response(response);
    return {};

}

/**
 * @param msg
 * Expects:
 * msg[NUMBER]: std::string
 */
status_t AccountMicroservice::remove(const std::string &card) {
    auto status = users.delete_one(session, document{} << Account::NUMBER << card << finalize);
    return {(status ? response::type::OK : response::type::NO_EXISTS)};

}

/**
 * @param msg
 * Expects:
 * msg[FROM]: std::string
 * msg[TO]: std::string
 * msg[AMOUNT]: double
 */
status_t AccountMicroservice::transaction(const std::string &from, const std::string &to, double amount) {

    auto status1 = users.update_one(session, document{} << Account::NUMBER << from << finalize,
                                    document{} << INC << open_document << Account::BALANCE << -1 * amount
                                               << close_document << finalize);
    auto status2 = users.update_one(session, document{} << Account::NUMBER << to << finalize,
                                    document{} << INC << open_document << Account::BALANCE << amount << close_document
                                               << finalize);
    return {((status1 && status2) ? response::type::OK : response::type::FAILED)};
}

/**
 * @param msg
 * Expects:
 * msg[NUMBER]: std::string
 */
status_t AccountMicroservice::exists(const std::string &card) {
    auto status = users.find_one(session, document{} << Account::NUMBER << card << finalize);
    return {(status ? response::type::EXISTS : response::type::NO_EXISTS)};

}

