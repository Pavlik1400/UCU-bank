#include "User.hpp"

void ucubank_api::v1::User::info(const drogon::HttpRequestPtr &req,
                                 std::function<void(const drg::HttpResponsePtr &)> &&callback,
                                 const std::string &login) const {

    LOG_DEBUG << "GET /ucubank_api/v1/user/info/" << login;

    Json::Value resp_json;
    resp_json["response"] = Json::Value{};
    // TODO: add get info logic
    resp_json["response"]["fname"] = "Pavlo";
    resp_json["response"]["lname"] = "Hilei";
    resp_json["response"]["balance"] = "2";
    resp_json["status"] = 200;
    auto resp = drg::HttpResponse::newHttpJsonResponse(resp_json);
    callback(resp);

}

void ucubank_api::v1::User::login(const drogon::HttpRequestPtr &req,
                                  std::function<void(const drg::HttpResponsePtr &)> &&callback,
                                  const std::string &login) const {
    LOG_DEBUG << "GET /ucubank_api/v1/user/login/" << login;
    Json::Value resp_json;
    resp_json["status"] = 200;

    auto req_json_ptr = req->getJsonObject();
    if (!req_json_ptr) {
        resp_json["status"] = 400,
                resp_json["msg"] = "Error while parsing json: " + req->getJsonError();
        return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
    }

    auto req_json = *req_json_ptr;
    if (req_json["hash"].empty()) {
        resp_json["msg"] = "Please specify hash field";
        resp_json["status"] = 400;
        return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
    }

    // TODO: add login logic
    LOG_DEBUG << "Password hash: " << req_json["hash"].as<str>();
    resp_json["response"] = Json::Value{};
    resp_json["response"]["allowed"] = true;
    //
    auto resp = drg::HttpResponse::newHttpJsonResponse(resp_json);
    callback(resp);
}

void ucubank_api::v1::User::register_(const drogon::HttpRequestPtr &req,
                                      std::function<void(const drg::HttpResponsePtr &)> &&callback,
                                      const std::string &login) {
    LOG_DEBUG << "GET /ucubank_api/v1/user/register/" << login;
    Json::Value resp_json;
    resp_json["status"] = 200;

    auto req_json_ptr = req->getJsonObject();
    if (!req_json_ptr) {
        resp_json["status"] = 400;
        resp_json["msg"] = "Error while parsing json: " + req->getJsonError();
        return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));

    }
    // TODO: add register logic
    auto req_json = *req_json_ptr;
    LOG_DEBUG << req_json.toStyledString();
    callback( drg::HttpResponse::newHttpJsonResponse(resp_json));
}