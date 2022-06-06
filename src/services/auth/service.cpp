#include "auth/service.hpp"
#include "auth/constants.hpp"
#include "client.hpp"
#include "notification/constants.h"
#include "service_tools/utils.hpp"
#include "service_tools/macro.hpp"
#include "user/client.h"
#include "user/constants.h"
#include <boost/log/trivial.hpp>
#include <iterator>
#include <optional>
#include <ostream>
#include <rpc/config.h>
#include <rpc/rpc_error.h>
#include <rpc/server.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/algorithm/string.hpp>
#include <sstream>
#include <string>
#include <chrono>


namespace auth {
    inline std::string auth_data_unit_to_str(AuthDU adu) {
        return "{\n\tcred: " + adu.cred + ",\n\tdata: " + adu.data + "\n}";
    }

    inline std::ostream &operator<<(std::ostream &os, const AuthDU &adu) {
        return os << auth_data_unit_to_str(adu);
    }

    Service::Service(const nlohmann::json &cnf)
            : BasicMicroservice(cnf["auth"]["rpc_port"].get<int>(),
                                "tcp://" + cnf["auth"]["reddis_address"].get<std::string>() +
                                ":" + std::to_string(cnf["auth"]["reddis_port"].get<int>())),
              user(cnf["user"]["rpc_address"].get<std::string>(), cnf["user"]["rpc_port"].get<int>()), notification(
                    cnf["notification"]["broker_address"].get<std::string>() + ":" +
                    cnf["notification"]["broker_port"].get<std::string>(),
                    cnf["notification"]["topic"].get<std::string>()),
              mock(cnf["auth"]["mock_mail"]) {
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
    }

    void Service::start() {
        CUSTOM_LOG(lg, info) << LOG_FUNC(Service::start);
        register_methods();
    }

    std::optional<std::string> Service::send_otp(const std::string &otp, const std::string &email) {
        CUSTOM_LOG(lg, info) << LOG_FUNC(Service::send_otp, otp, email);
        try {
            notification.send(notification_t{.identifier=email,
                    .payload="SECRET-KEY: " + otp,
                    .type=identifier_type::EMAIL});
            return boost::uuids::to_string(boost::uuids::random_generator()());
        } catch (std::exception &e) {
            return {};
        }
    }

    /**
     * @brief Perform first step of TwoFactorAuthentication 
     * 
     * @param id_n_pwd {
     *  .cred is user's PhoneNumber
     *  .data is user's Password
     * } 
     * @return std::pair<auth::status, AuthDU {
     *  if PhoneNumber and Password are correct
     *      .cred is temporary token
     *      .data is empty
     *  else
     *  

     }> 
     */
    std::pair<auth::status, AuthDU>
    Service::tfa_req_otp(const AuthDU &id_n_pwd) {
        CUSTOM_LOG(lg, info) << LOG_FUNC(Service::tfa_req_otp, id_n_pwd);
        auto &[phoneNo, password] = id_n_pwd;
        auto st = user.valid_password(phoneNo, password);
        std::cout << st << std::endl;
        switch (st) {
            case user::status::OK:
                break;
            case user::status::INVALID_PASSWORD:
                return {auth::status::INVALID_PASSWORD, {}};
            default:
                return {auth::status::GET_FAILED, {}};
        }
        auto [status, table]{user.get<user::by::PHONE_NO>(phoneNo, {.data=user::privilege::SUPER})};
        if (status != user::status::OK) return {auth::status::GET_FAILED, {}};
        auto otp{boost::uuids::to_string(uuid_gen())};
        auto otp_tk{send_otp(otp, table.email)};
        if (!otp_tk) return {auth::status::MAIL_FAILED, {}};
        hash_store<token_type::OneTimePswd>(*otp_tk, {otp, table.id, table.type});
//        return {auth::status::OK, {*otp_tk, {}}};
        return {auth::status::OK, {*otp_tk, mock ? otp : std::string()}};
    }


        /**
         * @brief Perform second step of TwoFactorAuthentication
         *
         * @param id_n_otp {
         *  .cred is temporary token,
         *  .data is OneTimePassword which has been sent to user's email
         * }
         * @return std::pair<auth::status, AuthDU>
         */
        std::pair<auth::status, AuthDU>
        Service::tfa_ver_otp(const AuthDU &id_n_otp) {
            CUSTOM_LOG(lg, info) << LOG_FUNC(Service::tfa_ver_otp, id_n_otp);
            const auto &[otp_tk, otp] = id_n_otp;
            auto val{hash_retrieve<token_type::OneTimePswd>(otp_tk)};
            if (!val) return {auth::status::HASH_FAILED, {}};
            auto &[exp_otp, uid, upriv] = *val;
            if (exp_otp != otp) return {auth::status::INVALID_PASSWORD, {}};
            hash_del<token_type::OneTimePswd>(otp_tk);
            auto tk{boost::uuids::to_string(uuid_gen())};
            hash_store<token_type::UserInfo>(tk, {uid, upriv});
            return {auth::status::OK, {uid, tk}};
        }

        /**
         * @brief Return UserId and UserPrivileges of user by token
         *
         * @param tk_{
         *  .cred is token,
         *  .data can be empty
         * }
         * @return std::pair<auth::status, AuthDU={
         *  .cred is UserId,
         *  .data is UserPrivileges
         * }>
         */
        std::pair<auth::status, AuthDU>
        Service::sess_info(const AuthDU &tk_) {

            CUSTOM_LOG(lg, info) << LOG_FUNC(Service::sess_info, tk_);
            auto &[tk, _]{tk_};
            auto val{hash_retrieve<token_type::UserInfo>(tk)};
            if (!val) return {status::GET_FAILED, {}};
            auto &[uid, upriv] = *val;
            return {status::OK, {uid, upriv}};
        }

        std::pair<auth::status, AuthDU>
        Service::sess_end(const AuthDU &tk_) {
            CUSTOM_LOG(lg, info) << LOG_FUNC(Service::sess_end, tk_);
            auto &[tk, _]{tk_};
            hash_del<token_type::UserInfo>(tk);
            return {status::OK, {}};
        }


        void Service::register_methods() {
            CUSTOM_LOG(lg, info) << LOG_FUNC(Service::register_methods);
            rpc_server.bind("tfa_pwd", [&](const AuthDU &id_n_pwd) { return tfa_req_otp(id_n_pwd); });
            rpc_server.bind("tfa_otp", [&](const AuthDU &id_n_otp) { return tfa_ver_otp(id_n_otp); });
            rpc_server.bind("sess_info", [&](const AuthDU &tk_n_info) { return sess_info(tk_n_info); });
            rpc_server.bind("sess_end", [&](const AuthDU &tk_n_info) { return sess_end(tk_n_info); });
        }

        void Service::finish() {
            CUSTOM_LOG(lg, info) << LOG_FUNC(Service::finish);
        }

        Service::~Service()
        {
            CUSTOM_LOG(lg, info) << LOG_FUNC(Service::~Service);
        }
    }
