#include "user.hpp"

namespace ucubank_api::v2 {
    User::User(const nlohmann::json &cnf) :
            APIBase(cnf),
            user_client(cnf["user"]["rpc_address"].get<str>(), cnf["user"]["rpc_port"].get<int>()) {
        logger.info("User API v2 initialized");
    }

    jsonv User::login1_h(const jsonv &req_json, jsonv &resp_json) {
        auto phone_num = req_json["phone_num"].as<str>();
        auto password = req_json["password"].as<str>();

        auto [status, key_secret] = auth_client.tfa_pwd({phone_num, password});
        if (status != auth::OK)
            return fail(auth::status_to_str(status), resp_json);

        auto [otp_k, otp] = key_secret;
        if (!otp.empty())
            resp_json["one_time_passwd"] = otp;

        resp_json["otp_key"] = otp_k;
        return resp_json;
    }

    jsonv User::login2_h(const jsonv &req_json, jsonv &resp_json) {
        auto otp_key = req_json["otp_key"].as<str>();
        auto otp = req_json["one_time_passwd"].as<str>();

        auto [status, uid_tk] = auth_client.tfa_otp({otp_key, otp});
        if (status != auth::OK)
            return fail(auth::status_to_str(status), resp_json);

        auto [uid, tk] = uid_tk;
        resp_json["uid"] = uid;
        resp_json["token"] = tk;

        return resp_json;
    }

    jsonv User::reg_h(const jsonv &req_json, jsonv &resp_json) {
        auto user = deserialize_user_t(req_json);
        if (user.type != user::privilege::REGULAR) {
            if (req_json[user::super_secret::KEY].empty())
                return fail("Not allowed to create any user type expect 'regular'", resp_json, 403);

            if (req_json[user::super_secret::KEY].as<str>() != user::super_secret::VALUE)
                return fail("FBI is coming for you...", resp_json, 403);
        }

        auto status = user_client.create(user);
        if (status != user::OK) {
            return fail(user::status_to_str(status), resp_json);
        }

        return resp_json;
    }

    jsonv User::info_h(const jsonv &req_json, jsonv &resp_json, const auth::AuthDU &privilege) {
        auto phone_number = req_json["phone_num"].as<str>();
        auto [status, user_info] = user_client.get<user::by::PHONE_NO>(phone_number, privilege);
        if (status != user::OK) {
            if (status == user::GET_FAILED) return fail("db error", resp_json, 500);
            return fail(user::status_to_str(status), resp_json);
        }

        resp_json["info"] = serialized_user_t(user_info);
        return resp_json;
    }

    jsonv User::remove_h(const jsonv &req_json, jsonv &resp_json, const auth::AuthDU &privilege) {
        auto phone_num = req_json["phone_num"].as<str>();

        auto remove_status = user_client.remove(phone_num, privilege);
        if (remove_status != user::OK)
            return fail(user::status_to_str(remove_status), resp_json);

        return resp_json;
    }

    jsonv User::logout_h(const jsonv &req_json, jsonv &resp_json, const auth::AuthDU &privilege) {
        auto token = req_json["token"].as<str>();
        auto [status, _] = auth_client.sess_end({.cred=token});
        if (status != auth::OK) {
            return fail(auth::status_to_str(status), resp_json);
        }
        return resp_json;
    }
}
///////////////////////////// SERIALIZATION /////////////////////////////

namespace ucubank_api::v2 {
    Json::Value serialized_user_t(const user_t &user_info) {
        Json::Value result{};
        if (!user_info.date_of_birth.empty()) result["date_of_birth"] = user_info.date_of_birth;
        if (!user_info.phoneNo.empty()) result["phone_num"] = user_info.phoneNo;
        if (!user_info.email.empty()) result["email"] = user_info.email;
        if (!user_info.address.empty()) result["address"] = user_info.address;
        if (!user_info.joining_date.empty()) result["joining_date"] = user_info.joining_date;
        if (!user_info.id.empty()) result["id"] = user_info.id;
        if (!user_info.name.empty()) result["name"] = user_info.name;
        if (!user_info.gender.empty()) result["gender"] = user_info.gender;
        if (!user_info.type.empty()) result["type"] = user_info.type;
//    if (!user_info.password.empty()) result["password"] = user_info.password;
        return result;
    }

    user_t deserialize_user_t(const Json::Value &json) {
        return {
                "",
                json["type"].as<str>(),
                json["name"].as<str>(),
                json["password"].as<str>(),
                json["date_of_birth"].as<str>(),
                json["phone_num"].as<str>(),
                json["email"].as<str>(),
                json["address"].as<str>(),
                json["gender"].as<str>(),
        };
    }

}
