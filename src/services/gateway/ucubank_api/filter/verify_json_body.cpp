#include "verify_json_body.hpp"
#include "ucubank_api/helpers.hpp"


void VerifyJsonBody::doFilter(const drogon::HttpRequestPtr &req, drogon::FilterCallback &&fcb,
                              drogon::FilterChainCallback &&fccb) {
    auto req_json_ptr = req->getJsonObject();
    if (!req_json_ptr) {
        auto resp_json = new Json::Value;
        (*resp_json)["status"] = 400;
        (*resp_json)["message"] = "Request error: " + req->getJsonError();
        IFDEBUG(std::cout << "[DBG]: " << "Request error: " + req->getJsonError() << "\n")
        return fcb(drogon::HttpResponse::newHttpJsonResponse(*resp_json));
    }
    fccb();
}
