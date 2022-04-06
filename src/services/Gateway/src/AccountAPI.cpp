#include "AccountAPI.hpp"


void ucubank_api::v1::Account::create(
        const drg::HttpRequestPtr &req,
        std::function<void(const drg::HttpResponsePtr &)> &&callback) const {
    LOG_DEBUG << "GET /ucubank_api/v1/account/create/";
    Json::Value resp_json;
    resp_json["status"] = 200;
    auto resp = drg::HttpResponse::newHttpJsonResponse(resp_json);
    callback(resp);
}
