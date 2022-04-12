#include "UserAPI.hpp"

ucubank_api::v1::UserAPI::UserAPI(const nlohmann::json &cnf) :
        userClient(cnf["user"]["rpc_address"].get<std::string>(), cnf["user"]["rpc_port"].get<int>()) {
    logger.info("User API initialized");

}

void ucubank_api::v1::UserAPI::info(const drogon::HttpRequestPtr &req,
                                    std::function<void(const drg::HttpResponsePtr &)> &&callback,
                                    const std::string &login) {

    logger.debug("GET /ucubank_api/v1/user/info/");
    auto[json, success] = getJsonObjectSafe(req);
    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(*json));
    auto req_json = *json;
    auto resp_json = Json::Value{};
    resp_json["status"] = 200;

    DEBUG_TRY

        if (req_json["name"].empty() || req_json["phone_num"].empty()) {
            resp_json["status"] = 400;
            resp_json["message"] = req_json["name"].empty() ? "'name' field is is not present"
                                                            : "'phone_num' field is is not present";
            return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
        }
        // TODO: verify if user is allowed to get all info


        resp_json["fname"] = "Pavlo";
        resp_json["lname"] = "Hilei";
        resp_json["balance"] = "2";
        auto resp = drg::HttpResponse::newHttpJsonResponse(resp_json);
        callback(resp);
    DEBUG_CATCH

}

void ucubank_api::v1::UserAPI::login(const drogon::HttpRequestPtr &req,
                                     std::function<void(const drg::HttpResponsePtr &)> &&callback,
                                     const std::string &login) {
    logger.debug("GET /ucubank_api/v1/user/info/");
    auto[json, success] = getJsonObjectSafe(req);
    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(*json));
    auto req_json = *json;
    auto resp_json = Json::Value{};
    resp_json["status"] = 200;

    DEBUG_TRY
        if (!verify_fields_present(req_json, resp_json, {"name", "phone_num", "hashed_password"}))
            return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));

        auto name = req_json["name"].as<std::string>();
        auto phone_num = req_json["phone_num"].as<std::string>();
        if (userClient.exists(name, phone_num) == user::USER_DOESNT_EXIST) {
            resp_json["status"] = 400;
            resp_json["message"] = "User doesn't exists";
            return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
        }

        // TODO: verify hashed password
        resp_json["allowed"] = true;
        resp_json["token"] = "0";
        callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
    DEBUG_CATCH
}

void ucubank_api::v1::UserAPI::register_(const drogon::HttpRequestPtr &req,
                                         std::function<void(const drg::HttpResponsePtr &)> &&callback,
                                         const std::string &login) {
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
