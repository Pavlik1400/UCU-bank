#include "Filters.hpp"

void LoginFilter::doFilter(const drogon::HttpRequestPtr &req, drogon::FilterCallback &&fcb,
                           drogon::FilterChainCallback &&fccb) {

    LOG_DEBUG << "Checking if user is logged";
    auto req_json_ptr = req->getJsonObject();
    auto resp_json = Json::Value{};
    if (!req_json_ptr) {
        resp_json["msg"] = "Error while parsing json: " + req->getJsonError();
        resp_json["status"] = 400;
        return fcb(drogon::HttpResponse::newHttpJsonResponse(resp_json));
    }

    auto req_json = *req_json_ptr;
    // TODO: add check logged logic

    fccb();
}
