#include "AccountAPI.hpp"


void ucubank_api::v1::AccountAPI::create(
        const drg::HttpRequestPtr &req,
        std::function<void(const drg::HttpResponsePtr &)> &&callback) {
    CUSTOM_LOG(logger, debug) << "GET /ucubank_api/v1/account/create/";
    auto [json, success] = getJsonObjectSave(req);
    if (!success) {
        return callback(drg::HttpResponse::newHttpJsonResponse(*json));
    }
    auto resp_json = *json;
    resp_json["status"] = 200;


    callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
}
