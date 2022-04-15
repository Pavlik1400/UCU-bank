#include "auth/service.hpp"
#include "auth/constants.hpp"
#include "service_tools/utils.hpp"
#include "UserClient.h"
#include "user_constants.h"
#include <boost/log/trivial.hpp>
#include <optional>
#include <rpc/config.h>
#include <rpc/rpc_error.h>
#include <rpc/server.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <string>
#include <chrono>

namespace auth {
    Service::Service(const nlohmann::json &cnf)
        : BasicMicroservice(cnf["auth"]["rpc_port"].get<int>(),
                          "tcp://" + cnf["auth"]["reddis_address"].get<std::string>() +
                          ":" + std::to_string(cnf["auth"]["reddis_port"].get<int>()))
        , user(cnf["user"]["rpc_address"].get<std::string>(), cnf["user"]["rpc_port"].get<int>())
    {
        CUSTOM_LOG(lg, info) << '\n'
        << "auth::Service::Sercie(\n"
        << '\t' << "BasicMicroservice(\n"
        << '\t' << '\t' << cnf["auth"]["rpc_port"].get<int>() << ",\n"
        << '\t' << '\t' << "tcp://" + cnf["auth"]["reddis_address"].get<std::string>() + ":"
                        + std::to_string(cnf["auth"]["reddis_port"].get<int>()) << ",\n"
        << '\t' << "),\n"
        << '\t' << "UserMicroservice(\n"
        << '\t' << '\t' << cnf["user"]["rpc_address"].get<std::string>() << ",\n"
        << '\t' << '\t' << cnf["user"]["rpc_port"].get<int>() << ",\n"
        << '\t' << "),\n"
        << ")";

        msender.with_sender("ucu.bank.24@gmail.com")
            .with_subject("Authentication");
    }

    void Service::start() {
        CUSTOM_LOG(lg, info) << '\n'
        << "auth::Service::strart()";
        register_methods();
    }
    
    std::optional<boost::uuids::uuid>
    Service::send_secret(const boost::uuids::uuid & secret,
        const std::string & email)
    {
        CUSTOM_LOG(lg, info) << '\n'
        << "auth::Service::send_secret(\n"
        << '\t' << secret << ",\n"
        << '\t' << email << ",\n"
        << ")";

        try {
            msender.with_receiver(email)
                .with_body("SECRET-KEY: " + boost::uuids::to_string(secret))
                .send();
            return boost::uuids::random_generator()();
        } catch (std::exception& e) {
            CUSTOM_LOG(lg, error) << "auth::Service::send_secret failed to sent secret: " << e.what();
            return {};
        }
    }

    bool
    Service::hash_secret(const boost::uuids::uuid & id,
        const boost::uuids::uuid & secret)
    {
        CUSTOM_LOG(lg, info) << "\n"
        << "auth::Service::hash_store(\n" 
        << '\t' << id << ",\n"
        << '\t' << secret << "\n"
        << ")";

        auto login_id{"login-ids"+boost::uuids::to_string(id)};
        if (!redis_client.set(login_id, boost::uuids::to_string(secret)) ) {
            CUSTOM_LOG(lg, error) << "auth::Service::hash_store failed to store secret in redis";
            return false;
        }
        if (!redis_client.expire(login_id, std::chrono::seconds(60))) {
            CUSTOM_LOG(lg, error) << "auth::Service::hash_store failed to make secret expirable";
            return false;
        }
        return true; 
    }

    std::pair<auth::status, std::string>
    Service::log1(const std::string &name, 
        const std::string &phoneNo,
        const std::string &pswd)
    {
        CUSTOM_LOG(lg, info) << '\n'
        << "auth::Service::log1(\n"
        << '\t' << name << ",\n"
        << '\t' << phoneNo << ",\n"
        << '\t' << pswd << "\n"
        ")";

        user::status status;
        user_t table;

        try {
            auto [status_, table_] = user.get(name, phoneNo);
            status=status_, table=table_;
        } catch (rpc::rpc_error & e) {
            CUSTOM_LOG(lg, info) << "auth::Service::log1: RPC_FAILED";
            return {auth::status::RPC_FAILED, {}};
        }

        switch (status) {
        case user::status::USER_DOESNT_EXIST:
            CUSTOM_LOG(lg, info) << "auth::Service::log1: INVALID_NAME_OR_PHONE";
            return {auth::status::INVALID_NAME_OR_PHONE, {}};

        case user::status::OK:
            break;

        default:
            CUSTOM_LOG(lg, info) << "auth::Service::log1: INVALID_DB_RESPONSE: " << std::to_string(status);
            return {auth::status::INVALID_DB_RESPONSE, {}};
        }

        if ( pswd != table.password ) {
            CUSTOM_LOG(lg, info) << "auth::Service::log1: INVALID_USER_PASSWORD";
            return {auth::status::INVALID_USER_PASSWORD, {}};
        }

        auto secret {uuid_gen()};
        auto auth_id{send_secret(secret, table.email)};
        if (!auth_id) {
            CUSTOM_LOG(lg, info) << "auth::Service::log1: MAIL_FAILED";
            return {auth::status::MAIL_FAILED, {}};
        }

        if (!hash_secret(*auth_id, secret)) {
            CUSTOM_LOG(lg, info) << "auth::Service::log1: HASH_FAILED";
            return {auth::status::HASH_FAILED, {}};
        }
        return { auth::status::OK, boost::uuids::to_string(*auth_id)};
    }
    
    std::pair<auth::status, std::string>
    Service::log2(const std::string & login_id, 
        const std::string & secret)
    {
        CUSTOM_LOG(lg, info) << '\n'
        << "auth::Service::log1(\n"
        << '\t' << login_id << ",\n"
        << '\t' << secret << '\n'
        << ")";
        return {auth::status::OK, {}};
    }

    void Service::register_methods() {
        CUSTOM_LOG(lg, info) << '\n'
        << "auth::Service::register_methods()";
        rpc_server.bind("log1", [&](const std::string &name, 
            const std::string &phoneNo,
            const std::string &pswd){return log1(name, phoneNo, pswd);}); 
        rpc_server.bind("log2", [&](const std::string & login_id, 
            const std::string & secret){return log2(login_id, secret);});
    }

    void Service::finish() {
        CUSTOM_LOG(lg, info) << "auth::Service::finish()";
    }

    Service::~Service() {
        CUSTOM_LOG(lg, info) << '\n'
        << "auth::Service::~Service()";
    }
}
