#include "gateway/user.hpp"

ucubank_api::v1::User::User(const nlohmann::json &cnf) :
        userClient(cnf["user"]["rpc_address"].get<std::string>(), cnf["user"]["rpc_port"].get<int>()) {
    logger.info("User API initialized");

}

void ucubank_api::v1::User::info(const drogon::HttpRequestPtr &req,
                                    std::function<void(const drg::HttpResponsePtr &)> &&callback) {

    logger.debug("GET /ucubank_api/v1/user/info/");
    auto[json, success] = getJsonObjectSafe(req);
    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(*json));
    auto req_json = *json;
    auto resp_json = Json::Value{};
    resp_json["status"] = 200;

    DEBUG_TRY
        if (!verify_fields_present(req_json, resp_json, {"name", "phone_num"}))
            return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
        // TODO: verify if user is allowed to get all info


        resp_json["fname"] = "Pavlo";
        resp_json["lname"] = "Hilei";
        resp_json["balance"] = "2";
        auto resp = drg::HttpResponse::newHttpJsonResponse(resp_json);
        callback(resp);
    DEBUG_CATCH

}

void ucubank_api::v1::User::login(const drogon::HttpRequestPtr &req,
                                     std::function<void(const drg::HttpResponsePtr &)> &&callback) {
    logger.debug("GET /ucubank_api/v1/user/login/");
    auto [success, req_json, resp_json] = prepare_json(req);
    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(req_json));

    DEBUG_TRY
        if (!verify_fields_present(req_json, resp_json, {"name", "phone_num", "hashed_password"}))
            return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));

        auto name = req_json["name"].as<std::string>();
        auto phone_num = req_json["phone_num"].as<std::string>();
        auto hashed_password = req_json["hashed_password"].as<std::string>();
        auto [status, user_info] = userClient.get(name, phone_num);
        if (status == user::USER_DOESNT_EXIST) return fail_response("User doesn't exists", callback, resp_json);
        if (status == user::GET_FAILED) return fail_response("db error", callback, resp_json, 500);
        if (user_info.password != hashed_password) return fail_response("Incorrect password", callback, resp_json, 403);

        // TODO: verify hashed password
        resp_json["allowed"] = true;
        resp_json["token"] = "0";
        callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
    DEBUG_CATCH
}

void ucubank_api::v1::User::register_(const drogon::HttpRequestPtr &req,
                                         std::function<void(const drg::HttpResponsePtr &)> &&callback) {
    logger.debug("GET /ucubank_api/v1/user/register/");
    auto[json, success] = getJsonObjectSafe(req);
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
