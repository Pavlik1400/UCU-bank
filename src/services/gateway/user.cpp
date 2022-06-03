#include "gateway/user.hpp"
#include "auth/constants.hpp"

ucubank_api::v1::User::User(const nlohmann::json &cnf) :
        user_client(cnf["user"]["rpc_address"].get<std::string>(), cnf["user"]["rpc_port"].get<int>()),
        auth_client(cnf) {
    logger.info("User API initialized");
}

void ucubank_api::v1::User::info(const drogon::HttpRequestPtr &req,
                                 std::function<void(const drg::HttpResponsePtr &)> &&callback) {

    logger.debug("GET /ucubank_api/v1/user/info/");
//    auto [success, req_json, resp_json] = prepare_json(req);
    auto [success, req_json, resp_json, privilege] = prepare_json_auth(req, auth_client);
    std::cout << "success: " << success << std::endl;
    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));

    DEBUG_TRY
        if (!verify_fields_present(req_json, resp_json, {"phone_num"}))
            return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));

        auto phone_number = req_json["phone_num"].as<std::string>();
        auto [status, user_info] = user_client.get<user::by::PHONE_NO>(phone_number, privilege);
        if (status != user::OK) {
            if (status == user::GET_FAILED) return fail_response("db error", callback, resp_json, 500);
            return fail_response(user::status_to_str(status), callback, resp_json);
        }

        // TODO: verify if user is allowed to get all info
        resp_json["info"] = serialized_user_t(user_info);
        callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
    DEBUG_CATCH

}

void ucubank_api::v1::User::login1(const drogon::HttpRequestPtr &req,
                                   std::function<void(const drg::HttpResponsePtr &)> &&callback) {
    logger.debug("GET /ucubank_api/v1/user/login1/");
    auto [success, req_json, resp_json] = prepare_json(req);
    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));

    DEBUG_TRY
        if (!verify_fields_present(req_json, resp_json, {"phone_num", "password"}))
            return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));

        auto phone_num = req_json["phone_num"].as<std::string>();
        auto password = req_json["password"].as<std::string>();
        std::cout << "num: " << phone_num << ", password: " << password << std::endl;
        auto [status, key_secret] = auth_client.tfa_pwd({phone_num, password});
        std::cout << "Status: " << status << ", key_secret: " << key_secret.cred << ", " << key_secret.data
                  << std::endl;
        if (status != auth::OK) {
            return fail_response(auth::status_to_str(status), callback, resp_json);
        }

        auto [otp_k, otp] = key_secret;
        if (!otp.empty()) {
            resp_json["one_time_passwd"] = otp;
        }

        resp_json["otp_key"] = otp_k;
        callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
    DEBUG_CATCH
}

void ucubank_api::v1::User::login2(const drogon::HttpRequestPtr &req,
                                   std::function<void(const drg::HttpResponsePtr &)> &&callback) {
    logger.debug("GET /ucubank_api/v1/user/login2/");
    auto [success, req_json, resp_json] = prepare_json(req);
    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(req_json));

    DEBUG_TRY
        if (!verify_fields_present(req_json, resp_json, {"one_time_passwd", "otp_key"}))
            return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));

        auto otp_key = req_json["otp_key"].as<std::string>();
        auto otp = req_json["one_time_passwd"].as<std::string>();
        auto [status, uid_tk] = auth_client.tfa_otp({otp_key, otp});
        if (status != auth::OK) {
            return fail_response(auth::status_to_str(status), callback, resp_json);
        }
        auto [uid, tk] = uid_tk;
        resp_json["uid"] = uid;
        resp_json["token"] = tk;
        callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
    DEBUG_CATCH

}

void ucubank_api::v1::User::register_(const drogon::HttpRequestPtr &req,
                                      std::function<void(const drg::HttpResponsePtr &)> &&callback) {
    logger.debug("GET /ucubank_api/v1/user/register/");
    auto [success, req_json, resp_json] = prepare_json(req);
    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));

    DEBUG_TRY
        if (!verify_fields_present(
                req_json, resp_json,
                {"type", "name", "password", "date_of_birth", "phoneNo", "email", "address", "gender"}))
            return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
        auto user = deserialize_user_t(req_json);
        if (user.type != user::privilege::REGULAR) {
            if (req_json[user::super_duper_secret::KEY].empty()) {
                return fail_response("Not allowed to create any user type expect 'regular'", callback, resp_json, 403);
            }
            if (req_json[user::super_duper_secret::KEY].as<std::string>() != user::super_duper_secret::VALUE) {
                return fail_response("FBI is coming for you...", callback, resp_json, 403);
            }
        }

        auto status = user_client.create(user);
        if (status != user::OK) return fail_response(user::status_to_str(status), callback, resp_json);
        callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
    DEBUG_CATCH
}

void ucubank_api::v1::User::remove(const drogon::HttpRequestPtr &req,
                                   std::function<void(const drg::HttpResponsePtr &)> &&callback) {
    logger.debug("DELETE /ucubank_api/v1/user/remove/");
    auto [success, req_json, resp_json, privilege] = prepare_json_auth(req, auth_client);
    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));

    DEBUG_TRY
        if (!verify_fields_present(req_json, resp_json, {"phoneNo"}))
            return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
        auto phoneNo = req_json["phoneNo"].as<std::string>();
        auto remove_status = user_client.remove(phoneNo, privilege);
        if (remove_status != user::OK) return fail_response(user::status_to_str(remove_status), callback, resp_json);
        callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
    DEBUG_CATCH

}

void ucubank_api::v1::User::logout(const drogon::HttpRequestPtr &req,
                                   std::function<void(const drg::HttpResponsePtr &)> &&callback) {
    logger.debug("DELETE /ucubank_api/v1/user/remove/");
    auto [success, req_json, resp_json, privilege] = prepare_json_auth(req, auth_client);
    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));

    DEBUG_TRY
//        auto invalidate_status = auth_client.invalidate(privilege.data);
//        if (invalidate_status != auth::OK) return fail_response(auth::status_to_str(invalidate_status), callback, resp_json);
        callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
    DEBUG_CATCH

}

Json::Value ucubank_api::v1::serialized_user_t(const user_t &user_info) {
    // TODO: find more clever way to serialize
    Json::Value result{};
    if (!user_info.date_of_birth.empty()) result["date_of_birth"] = user_info.date_of_birth;
    if (!user_info.phoneNo.empty()) result["phoneNo"] = user_info.phoneNo;
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

user_t ucubank_api::v1::deserialize_user_t(const Json::Value &json) {
    // TODO: find more clever way to deserealize
    return {
            "",
            json["type"].as<std::string>(),
            json["name"].as<std::string>(),
            json["password"].as<std::string>(),
            json["date_of_birth"].as<std::string>(),
            json["phoneNo"].as<std::string>(),
            json["email"].as<std::string>(),
            json["address"].as<std::string>(),
            json["gender"].as<std::string>(),
    };
}
