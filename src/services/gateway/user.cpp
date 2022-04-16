#include "gateway/user.hpp"
#include "auth/constants.hpp"

ucubank_api::v1::User::User(const nlohmann::json &cnf) :
        user_client(cnf["user"]["rpc_address"].get<std::string>(), cnf["user"]["rpc_port"].get<int>()) {
    logger.info("User API initialized");

}

void ucubank_api::v1::User::info(const drogon::HttpRequestPtr &req,
                                 std::function<void(const drg::HttpResponsePtr &)> &&callback) {

    logger.debug("GET /ucubank_api/v1/user/info/");
    auto [success, req_json, resp_json] = prepare_json(req);
    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(req_json));

    DEBUG_TRY
        if (!verify_fields_present(req_json, resp_json, {"name", "phone_num"}))
            return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
        // TODO: verify if user is allowed to get all info

        auto name = req_json["name"].as<std::string>();
        auto phone_number = req_json["phone_num"].as<std::string>();
        auto [status, user_info] = user_client.get(name, phone_number);
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
        if (!verify_fields_present(req_json, resp_json, {"name", "phone_num", "hashed_password"}))
            return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));

        auto name = req_json["name"].as<std::string>();
        auto phone_num = req_json["phone_num"].as<std::string>();
        auto hashed_password = req_json["hashed_password"].as<std::string>();
        auto [status, key] = auth_client.log1(name, phone_num, hashed_password);
        if (status != auth::OK) return fail_response(auth::status_to_str(status), callback, resp_json);

        // TODO: verify hashed password
        resp_json["key"] = key;
        callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
    DEBUG_CATCH
}

void ucubank_api::v1::User::login2(const drogon::HttpRequestPtr &req,
                                   std::function<void(const drg::HttpResponsePtr &)> &&callback) {
    logger.debug("GET /ucubank_api/v1/user/login1/");
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
    auto [json, success] = getJsonObjectSafe(req);
    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(*json));
    auto req_json = *json;
    auto resp_json = Json::Value{};

    auto req_json_ptr = req->getJsonObject();
    if (!req_json_ptr) {
        resp_json["status"] = 400;
        resp_json["msg"] = "Error while parsing json: " + req->getJsonError();
        return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));

    }
    // TODO: add register logic
//    auto req_json = *req_json_ptr;
//    LOG_DEBUG << req_json.toStyledString();
    callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
}
