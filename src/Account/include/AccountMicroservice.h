#ifndef UCU_BANK_ACCOUNTMICROSERVICE_H
#define UCU_BANK_ACCOUNTMICROSERVICE_H

#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/exception/exception.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>
#include "BasicMicroservice.hpp"
#include "constants.h"
#include "Account.h"

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::sub_array;

//namespace n = nlohmann;
class AccountMicroservice : public BasicMicroservice {

private:
    const std::string SET      = "$set";
    const std::string PUSH     = "$push";
    const std::string PULL     = "$pull";
    const std::string IN       = "$in";

    mongocxx::instance instance{}; // This should be done only once.
    mongocxx::uri uri{"mongodb://localhost:27017/?replicaSet=rs0"};
    mongocxx::client client = mongocxx::client(uri);
    mongocxx::database db;

    // collections in DB
    mongocxx::collection users;
    mongocxx::write_concern wc_majority{};
    mongocxx::read_concern rc_local{};
    mongocxx::read_preference rp_primary{};
    mongocxx::options::transaction sopts;
    mongocxx::client_session session = client.start_session();
    std::map<int, void (AccountMicroservice::*)(const nlohmann::json &)> selector = {
            {request::type::CREATE, &AccountMicroservice::create},
            {request::type::GET, &AccountMicroservice::get},
            {request::type::UPDATE, &AccountMicroservice::update},
            {request::type::REMOVE, &AccountMicroservice::remove}
    };

public:
    void custom_start() override;
    void receive_callback(const nlohmann::json &msg) override;
    void create(const nlohmann::json &msg);
    void get(const nlohmann::json &msg);
    void update(const nlohmann::json &msg);
    void remove(const nlohmann::json &msg);
};


#endif //UCU_BANK_ACCOUNTMICROSERVICE_H