#include "auth/service.hpp"
#include "MailSender.h"
#include "auth/constants.hpp"
#include "client.hpp"
#include "service_tools/utils.hpp"
#include "user/client.h"
#include "user/constants.h"
#include <boost/log/trivial.hpp>
#include <iterator>
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
    namespace {
        std::string tmp_upriv_tpx{"tmp_upriv_tpx"};
        std::string tmp_uid_tpx{"tmp_uid_tpx"};
        std::string otp_tpx{"otp_tpx"};
        std::string upriv_tpx{"upriv_tpx"};
        std::string uid_tpx{"uid_tpx"};
    }

    Service::Service(const nlohmann::json &cnf)
        : BasicMicroservice(cnf["auth"]["rpc_port"].get<int>(),
                          "tcp://" + cnf["auth"]["reddis_address"].get<std::string>() +
                          ":" + std::to_string(cnf["auth"]["reddis_port"].get<int>()))
        , user(cnf["user"]["rpc_address"].get<std::string>(), cnf["user"]["rpc_port"].get<int>())
        , mock(cnf["auth"]["mock_mail"])
        , msender(mock)
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

    std::optional<std::string>
    Service::send_otp(const std::string & otp,
        const std::string & email)
    {
        CUSTOM_LOG(lg, info) << '\n'
        << "auth::Service::send_secret(\n"
        << '\t' << otp << ",\n"
        << '\t' << email << ",\n"
        << ")";

        try {
            msender.with_receiver(email)
                .with_body("SECRET-KEY: " + otp)
                .send();
            return boost::uuids::to_string(boost::uuids::random_generator()());
        } catch (std::exception& e) {
            CUSTOM_LOG(lg, error) << "auth::Service::send_secret failed to sent secret: " << e.what();
            return {};
        }
    }

    bool
    Service::store(const std::string & key,
        const std::string & val,
        const long & ttl
    )
    {
        CUSTOM_LOG(lg, info) << "\n"
        << "auth::Service::store(\n"
        << '\t' << key << ",\n"
        << '\t' << val << "\n"
        << '\t' << ttl << "\n"
        << ")";

        redis_client.setex(key, ttl, val);
        return true;
    }

    std::pair<auth::status, AuthDU>
    Service::tfa_req_otp(const AuthDU & id_n_pwd)
    {
        CUSTOM_LOG(lg, info) << '\n'
        << "auth::Service::log1(\n"
        << '\t' << id_n_pwd.cred << ",\n"
        << '\t' << id_n_pwd.data << "\n"
        ")";
        auto & [phoneNo, password] = id_n_pwd;
        user::status status;
        user_t table;

        try {
            auto [status_, table_] = user.get(phoneNo);
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

        if ( password != table.password ) {
            CUSTOM_LOG(lg, info) << "auth::Service::log1: INVALID_USER_PASSWORD";
            return {auth::status::INVALID_USER_PASSWORD, {}};
        }

        auto otp {boost::uuids::to_string(uuid_gen())};
        auto otp_tk{send_otp(otp, table.email)};
        if (!otp_tk) {
            CUSTOM_LOG(lg, info) << "auth::Service::log1: MAIL_FAILED";
            return {auth::status::MAIL_FAILED, {}};
        }

        store(otp_tpx+*otp_tk, otp, 600);
        store(tmp_uid_tpx+*otp_tk, table.id, 600);
        store(tmp_upriv_tpx+*otp_tk, table.type, 600);

        return { auth::status::OK, {*otp_tk, mock? otp: std::string()}
        };
    }

    std::pair<auth::status, AuthDU>
    Service::tfa_ver_otp(const AuthDU & id_n_otp)
    {
        CUSTOM_LOG(lg, info) << '\n'
        << "auth::Service::log1(\n"
        << '\t' << id_n_otp.cred << ",\n"
        << '\t' << id_n_otp.data << '\n'
        << ")";
        auto & [otp_tk, otp] = id_n_otp;

        auto exp_otp{redis_client.get(otp_tpx + otp_tk)};
        if (!exp_otp) {
            std::cerr << "Invalid login_id" << std::endl;
            return {auth::status::HASH_FAILED, {}};
        }

        std::cerr << "RES: " << *exp_otp << std::endl;

        if ( *exp_otp != otp ) {
            std::cerr << "Invalid secret" << std::endl;
            return {auth::status::INVALID_USER_PASSWORD, {}};
        }

        auto uid {redis_client.get(tmp_uid_tpx+otp_tk)};    
        if ( !uid ) {
            std::cerr << "FAILED to get uid" << std::endl;
            return {auth::status::HASH_FAILED, {}};
        }
        auto upriv {redis_client.get(tmp_upriv_tpx+otp_tk)};    
        if ( !upriv ) {
            std::cerr << "FAILED to get upriv" << std::endl;
            return {auth::status::HASH_FAILED, {}};
        }

        redis_client.del(otp_tpx + otp_tk);
        redis_client.del(tmp_uid_tpx + otp_tk);
        redis_client.del(tmp_upriv_tpx + otp_tk);

        auto tk {boost::uuids::to_string(uuid_gen())};
        store(uid_tpx+tk, *uid, 6000);        
        store(upriv_tpx+tk, *upriv, 6000);        
        return {auth::status::OK, {*uid, tk}};
    }

    std::pair<auth::status, AuthDU>
    Service::sess_info(const AuthDU & tk_n_info)
    {
        auto & [tk, info] {tk_n_info};

        if (info != uid_tpx &&
            info != upriv_tpx) {
           return {status::INVALID_CARD_NUMBER, {}}; 
        }
        auto ret = redis_client.get(info + tk); 
        if (!ret) {
            return {status::GET_FAILED, {}};
        }
        return {status::OK, {{}, *ret}};
    }

    void Service::register_methods() {
        CUSTOM_LOG(lg, info) << '\n'
        << "auth::Service::register_methods()";
        rpc_server.bind("tfa_pwd", [&](const AuthDU & id_n_pwd){return tfa_req_otp(id_n_pwd);});
        rpc_server.bind("tfa_otp", [&](const AuthDU & id_n_otp){return tfa_ver_otp(id_n_otp);});
        rpc_server.bind("sess_info", [&](const AuthDU & tk_n_info){return sess_info(tk_n_info);});
    }

    void Service::finish() {
        CUSTOM_LOG(lg, info) << "auth::Service::finish()";
    }

    Service::~Service() {
        CUSTOM_LOG(lg, info) << '\n'
        << "auth::Service::~Service()";
    }
}
