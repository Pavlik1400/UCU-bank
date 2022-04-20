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
    auto [success, req_json, resp_json] = prepare_json(req);
    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(req_json));

    DEBUG_TRY
        if (!verify_fields_present(req_json, resp_json, {"phone_num"}))
            return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
        // TODO: verify if user is allowed to get all info

        auto phone_number = req_json["phone_num"].as<std::string>();
        auto [status, user_info] = user_client.get(phone_number);
        if (status != user::OK) {
            if (status == user::GET_FAILED) return fail_response("db error", callback, resp_json, 500);
            return fail_response(user::status_to_str(status), callback, resp_json);
        }

        // TODO: find more clever way to serialize
        resp_json["info"] = Json::Value{};
        resp_json["info"]["id"] = user_info.id;
        resp_json["info"]["type"] = user_info.type;
        resp_json["info"]["name"] = user_info.name;
//            resp_json["info"]["password"] = user_info.password;
        resp_json["info"]["date_of_birth"] = user_info.date_of_birth;
        resp_json["info"]["phoneNo"] = user_info.phoneNo;
        resp_json["info"]["email"] = user_info.email;
        resp_json["info"]["address"] = user_info.address;
        resp_json["info"]["gender"] = user_info.gender;
        resp_json["info"]["joining_date "] = user_info.joining_date;
        callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
    DEBUG_CATCH

}

void ucubank_api::v1::User::login1(const drogon::HttpRequestPtr &req,
                                   std::function<void(const drg::HttpResponsePtr &)> &&callback) {
    logger.debug("GET /ucubank_api/v1/user/login1/");
    auto [success, req_json, resp_json] = prepare_json(req);
    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(req_json));

    DEBUG_TRY
        if (!verify_fields_present(req_json, resp_json, {"phone_num", "hashed_password"}))
            return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));

        auto phone_num = req_json["phone_num"].as<std::string>();
        auto hashed_password = req_json["hashed_password"].as<std::string>();
        auto [status, key] = auth_client.log1(phone_num, hashed_password);
        if (status != auth::OK) return fail_response(auth::status_to_str(status), callback, resp_json);

        // TODO: verify hashed password
        resp_json["auth_id"] = key;
        callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
    DEBUG_CATCH
}

void ucubank_api::v1::User::login2(const drogon::HttpRequestPtr &req,
                                   std::function<void(const drg::HttpResponsePtr &)> &&callback) {
    logger.debug("GET /ucubank_api/v1/user/login2/");
    auto [success, req_json, resp_json] = prepare_json(req);
    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(req_json));

    DEBUG_TRY
        if (!verify_fields_present(req_json, resp_json, {"auth_id", "secret"}))
            return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));

        auto auth_id = req_json["auth_id"].as<std::string>();
        auto secret = req_json["secret"].as<std::string>();
        auto [status, token] = auth_client.log2(auth_id, secret);
        if (status != auth::OK) return fail_response(auth::status_to_str(status), callback, resp_json);

        // TODO: verify hashed password
        resp_json["token"] = token;
        callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
    DEBUG_CATCH

}

void ucubank_api::v1::User::register_(const drogon::HttpRequestPtr &req,
                                      std::function<void(const drg::HttpResponsePtr &)> &&callback) {
    logger.debug("GET /ucubank_api/v1/user/register/");
    auto [success, req_json, resp_json] = prepare_json(req);
    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(req_json));

    DEBUG_TRY
        if (!verify_fields_present(
                req_json, resp_json,
                {
                        "type", "name", "password", "date_of_birth", "phoneNo", "email", "address", "gender"
                }
        ))
            return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));

        // TODO: find more clever way to deserealize
        auto status = user_client.create({
            "",
            req_json["type"].as<std::string>(),
            req_json["name"].as<std::string>(),
            req_json["password"].as<std::string>(),
            req_json["date_of_birth"].as<std::string>(),
            req_json["phoneNo"].as<std::string>(),
            req_json["email"].as<std::string>(),
            req_json["address"].as<std::string>(),
            req_json["gender"].as<std::string>(),
        });

        if (status != user::OK) return fail_response(user::status_to_str(status), callback, resp_json);
        callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
    DEBUG_CATCH
    // TODO: add register logic
//    auto req_json = *req_json_ptr;
//    LOG_DEBUG << req_json.toStyledString();
}
