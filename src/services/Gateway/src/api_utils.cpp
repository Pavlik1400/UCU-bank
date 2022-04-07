#include "api_utils.hpp"

std::pair<std::shared_ptr<Json::Value>, bool> getJsonObjectSave(const drg::HttpRequestPtr &req) {
    auto req_json_ptr = req->getJsonObject();
    if (!req_json_ptr) {
        Json::Value resp_json;
        resp_json["status"] = 400;
        resp_json["msg"] = "Error while parsing json: " + req->getJsonError();
        return {std::make_shared<Json::Value>(resp_json), false};
    }
    return {req_json_ptr, true};
}
