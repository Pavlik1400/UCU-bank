#ifndef UCU_BANK_ACCOUNT_SERVICE_H
#define UCU_BANK_ACCOUNT_SERVICE_H

#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/exception/exception.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>
#include "basic/BasicMicroservice.hpp"
#include "account/constants.h"
#include "user/client.h"

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::sub_array;

namespace account {
    class Service : public BasicMicroservice {

    private:
        const std::string SET = "$set";
        const std::string PUSH = "$push";
        const std::string PULL = "$pull";
        const std::string IN = "$in";
        const std::string INC = "$inc";
        const std::string OID = "$oid";

        mongocxx::instance instance{}; // This should be done only once.
//        mongocxx::uri uri{"mongodb://mongo-db:27017/?replicaSet=r0"};
        const mongocxx::uri uri;
        mongocxx::client client = mongocxx::client(uri);
        mongocxx::database db;

        // collections in DB
        mongocxx::collection accounts;
        mongocxx::write_concern wc_majority{};
        mongocxx::read_concern rc_local{};
        mongocxx::read_preference rp_primary{};
        mongocxx::options::transaction sopts;
        mongocxx::client_session session = client.start_session();

        void register_methods();
        const nlohmann::json cnf;
        user::Client userClient;

    public:
        explicit Service(const nlohmann::json &cnf);

        void start() override;

        void finish() override;

        account::status create(const std::string &user_id, const std::string &account_type);

        std::pair<account::status, account_t> get(const std::string &card);

        std::pair<account::status, std::vector<account_t>> get_all(const std::string &user_id);

        account::status remove(const std::string &card);

        account::status transaction(const std::string &from, const std::string &to, double amount);

        account::status exists(const std::string &card);
    };
}




#endif //UCU_BANK_ACCOUNT_SERVICE_H
