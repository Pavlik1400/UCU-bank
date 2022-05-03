#ifndef UCU_BANK_USER_SERVICE_H
#define UCU_BANK_USER_SERVICE_H

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
#include "user/constants.h"

namespace user {
    using bsoncxx::builder::stream::close_array;
    using bsoncxx::builder::stream::close_document;
    using bsoncxx::builder::stream::document;
    using bsoncxx::builder::stream::finalize;
    using bsoncxx::builder::stream::open_array;
    using bsoncxx::builder::stream::open_document;
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::sub_array;

    class Service : public BasicMicroservice {

    private:
        const std::string SET = "$set";
        const std::string PUSH = "$push";
        const std::string PULL = "$pull";
        const std::string IN = "$in";
        const std::string INC = "$inc";
        const std::string OID = "$oid";

        mongocxx::instance instance{}; // This should be done only once.
        mongocxx::uri uri{"mongodb://localhost:27017/?replicaSet=rs0"};
//        mongocxx::uri uri{"mongodb://mongo-db:27017/?replicaSet=r0"};
        mongocxx::client client = mongocxx::client(uri);
        mongocxx::database db;

        // collections in DB
        mongocxx::collection users;
        mongocxx::write_concern wc_majority{};
        mongocxx::read_concern rc_local{};
        mongocxx::read_preference rp_primary{};
        mongocxx::options::transaction sopts;
        mongocxx::client_session session = client.start_session();

        const nlohmann::json cnf;

        void register_methods();

    public:
        explicit Service(const nlohmann::json &cnf);

        void start() override;

        void finish() override;

        user::status create(const user_t &user);

        std::pair<user::status, user_t> get(const std::string &phoneNo);

        user::status remove(const std::string &phoneNo);

        user::status exists(const std::string &phoneNo);

        user::status valid_id(const std::string &id);
    };
}



#endif //UCU_BANK_USER_SERVICE_H
