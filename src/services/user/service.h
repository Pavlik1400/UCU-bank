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
#include "auth/constants.hpp"

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
        const mongocxx::uri uri;
        mongocxx::client client = mongocxx::client(uri);
        mongocxx::database db;

        // collections in DB
        mongocxx::collection users;
        mongocxx::collection password_salt;
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

        template<by filter>
        std::pair<user::status, user_t> get(const std::string &identifier, const auth::AuthDU &ctrl);

//        std::pair<user::status, user_t> get(const std::string &phoneNo);

        user::status remove(const std::string &phoneNo, const auth::AuthDU &ctrl);

        user::status exists(const std::string &phoneNo);

        user::status valid_id(const std::string &id);

        user::status valid_password(const std::string &phoneNo, const std::string &password);
    };

    template<by filter>
    constexpr auto map_to_field()
    {
        switch(filter) {
            case by::ID:   return user::ID;
            case by::EMAIL: return user::EMAIL;
            case by::PHONE_NO:  return user::PHONE_NO;
        }
    }

    template<by filter>
    std::pair<user::status, user_t> Service::get(const std::string &identifier, const auth::AuthDU &ctrl) {
        CUSTOM_LOG(lg, debug) << "Get call";
        bsoncxx::stdx::optional<bsoncxx::document::value> result;
        if constexpr(filter == user::by::ID) {
            result = users.find_one(session, document{} << map_to_field<filter>() << bsoncxx::oid{bsoncxx::stdx::string_view{identifier}} << finalize);
        } else {
            result = users.find_one(session, document{} << map_to_field<filter>() << identifier << finalize);
        }
        user_t user{};

        if (result) {
            try {
                auto content = result->view();
                auto id = content[user::ID].get_oid().value.to_string();

                user.name = content[user::NAME].get_utf8().value.to_string();
                user.email = content[user::EMAIL].get_utf8().value.to_string();
                user.type = content[user::TYPE].get_utf8().value.to_string();

                if(ctrl.cred == id || ctrl.data == privilege::ADMIN || ctrl.data == privilege::SUPER) {
                    user.id = id;
                    user.date_of_birth = content[user::DATE_OF_BIRTH].get_utf8().value.to_string();
                    user.phoneNo = content[user::PHONE_NO].get_utf8().value.to_string();
                    user.address = content[user::ADDRESS].get_utf8().value.to_string();
                    user.gender = content[user::GENDER].get_utf8().value.to_string();
                    user.joining_date = content[user::JOINING_DATE].get_utf8().value.to_string();
                }

                if (ctrl.data == privilege::SUPER) {
                    user.password = content[user::PASSWORD].get_utf8().value.to_string();
                }


//                auto content = result->view();
//                user.id = content[user::ID].get_oid().value.to_string();
//                user.type = content[user::TYPE].get_utf8().value.to_string();
//                user.name = content[user::NAME].get_utf8().value.to_string();
//                user.password = content[user::PASSWORD].get_utf8().value.to_string();
//                user.date_of_birth = content[user::DATE_OF_BIRTH].get_utf8().value.to_string();
//                user.phoneNo = content[user::PHONE_NO].get_utf8().value.to_string();
//                user.email = content[user::EMAIL].get_utf8().value.to_string();
//                user.address = content[user::ADDRESS].get_utf8().value.to_string();
//                user.gender = content[user::GENDER].get_utf8().value.to_string();
//                user.joining_date = content[user::JOINING_DATE].get_utf8().value.to_string();
            } catch (...) {
                return {user::status::GET_FAILED, {}};
            }

        }
        return {result ? user::status::OK : user::status::USER_DOESNT_EXIST, user};
    }
}





#endif //UCU_BANK_USER_SERVICE_H
