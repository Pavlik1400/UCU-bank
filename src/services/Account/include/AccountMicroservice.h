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
#include "account_constants.h"

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::sub_array;

class AccountMicroservice : public BasicMicroservice {

private:
    const std::string SET = "$set";
    const std::string PUSH = "$push";
    const std::string PULL = "$pull";
    const std::string IN = "$in";
    const std::string INC = "$inc";
    const std::string OID = "$oid";

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

    void register_methods();

public:
    using BasicMicroservice::BasicMicroservice;
    void start() override;

    void finish() override;

    account::status create(const std::string &user_id, const std::string &account_type);

    std::pair<account::status, account_t> get(const std::string &card);

    account::status remove(const std::string &card);

    account::status transaction(const std::string &from, const std::string &to, double amount);

    account::status exists(const std::string &card);
};


#endif //UCU_BANK_ACCOUNTMICROSERVICE_H
