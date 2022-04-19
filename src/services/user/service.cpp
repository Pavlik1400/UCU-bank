#include "user/service.h"
#include "user/constants.h"
#include "service_tools/utils.hpp"

namespace user {

    Service::Service(const nlohmann::json &cnf) : BasicMicroservice(cnf["user"]["rpc_port"].get<int>(),
                                                                    "tcp://" +
                                                                    cnf["user"]["reddis_address"].get<std::string>() +
                                                                    ":" + std::to_string(
                                                                            cnf["user"]["reddis_port"].get<int>())),
                                                  cnf(cnf) {
        db = client["bank"];
        users = db["users"];
        users.create_index(session, document{} << user::PHONE_NO << 1 << finalize);
        wc_majority.acknowledge_level(mongocxx::write_concern::level::k_majority);
        rc_local.acknowledge_level(mongocxx::read_concern::level::k_local);
        rp_primary.mode(mongocxx::read_preference::read_mode::k_primary);
        sopts.write_concern(wc_majority);
        sopts.read_concern(rc_local);
        sopts.read_preference(rp_primary);
        CUSTOM_LOG(lg, debug) << "User service initialized";
    }


    void Service::start() {
        register_methods();
        CUSTOM_LOG(lg, info) << "Service has started successfully";
    }

    void Service::finish() {
        CUSTOM_LOG(lg, info) << "Service has finished";
    }


    user::status Service::create(const user_t &user) {
        CUSTOM_LOG(lg, debug) << "Create call";
        if (user.name.empty() or user.phoneNo.empty()) {
            return user::status::INCOMPLETE_USER_IDENTITY;
        }
        if (user.password.empty()) {
            return user::status::MISSING_PASSWORD;
        }

        if (users.find_one(session,
                           document{} << user::NAME << user.name << user::PHONE_NO << user.phoneNo << finalize)) {
            return user::USER_EXISTS;
        }

        auto doc = document{} << user::TYPE << user.type << user::NAME << user.name << user::PASSWORD << user.password
                              << user::DATE_OF_BIRTH << user.date_of_birth << user::PHONE_NO << user.phoneNo
                              << user::EMAIL << user.email << user::ADDRESS << user.address << user::GENDER
                              << user.gender << user::JOINING_DATE << generate_current_datetime() << finalize;
        auto status = users.insert_one(session, doc.view());

        return status ? user::status::OK : user::status::CREATION_FAILED;
    }


    std::pair<user::status, user_t> Service::get(const std::string &name, const std::string &phoneNo) {
        CUSTOM_LOG(lg, debug) << "Get call";
        auto result = users.find_one(session,
                                     document{} << user::NAME << name << user::PHONE_NO << phoneNo << finalize);
        user_t user;

        if (result) {
            try {
                auto content = result->view();
                user.id = content[user::ID].get_oid().value.to_string();
                user.type = content[user::TYPE].get_utf8().value.to_string();
                user.name = content[user::NAME].get_utf8().value.to_string();
                user.password = content[user::PASSWORD].get_utf8().value.to_string();
                user.date_of_birth = content[user::DATE_OF_BIRTH].get_utf8().value.to_string();
                user.phoneNo = content[user::PHONE_NO].get_utf8().value.to_string();
                user.email = content[user::EMAIL].get_utf8().value.to_string();
                user.address = content[user::ADDRESS].get_utf8().value.to_string();
                user.gender = content[user::GENDER].get_utf8().value.to_string();
                user.joining_date = content[user::JOINING_DATE].get_utf8().value.to_string();
            } catch (...) {
                return {user::status::GET_FAILED, {}};
            }

        }

        return {result ? user::status::OK : user::status::USER_DOESNT_EXIST, user};

    }

    user::status Service::remove(const std::string &name, const std::string &phoneNo) {
        CUSTOM_LOG(lg, debug) << "Remove call";
        auto status = users.delete_one(session,
                                       document{} << user::NAME << name << user::PHONE_NO << phoneNo << finalize);
        return status ? user::status::OK : user::status::USER_DOESNT_EXIST;

    }


    user::status Service::exists(const std::string &name, const std::string &phoneNo) {
        CUSTOM_LOG(lg, debug) << "Exists call";
        auto status = users.find_one(session,
                                     document{} << user::NAME << name << user::PHONE_NO << phoneNo << finalize);
        return status ? user::status::OK : user::status::USER_DOESNT_EXIST;
    }

    user::status Service::valid_id(const std::string &id) {
        CUSTOM_LOG(lg, debug) << "Exists call";
        auto status = users.find_one(session, document{} << user::ID << bsoncxx::oid{bsoncxx::stdx::string_view{id}}
                                                         << finalize);
        return status ? user::status::OK : user::status::USER_DOESNT_EXIST;
    }

    void Service::register_methods() {
        rpc_server.bind("create", [&](const user_t &user) {
            return create(user);
        });
        rpc_server.bind("get", [&](const std::string &name, const std::string &phoneNo) { return get(name, phoneNo); });
        rpc_server.bind("remove",
                        [&](const std::string &name, const std::string &phoneNo) { return remove(name, phoneNo); });
        rpc_server.bind("exists",
                        [&](const std::string &name, const std::string &phoneNo) { return exists(name, phoneNo); });
        rpc_server.bind("valid_id", [&](const std::string &id) {
            return valid_id(id);
        });

    }
}



