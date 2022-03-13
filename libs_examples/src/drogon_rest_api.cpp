#include "drogon_rest_api.h"

void api::v1::User::getInfo(const drg::HttpRequestPtr &req, std::function<void(const drg::HttpResponsePtr &)> &&callback,
                       int userId) const {
    std::cout << "GET /" << userId << std::endl;
    Json::Value json;
    json["userId"] = userId;
    json["detailinfo"] = false;
    json["status"] = "200";
    auto resp = drg::HttpResponse::newHttpJsonResponse(json);
    callback(resp);
}

void api::v1::User::getDetailInfo(const drg::HttpRequestPtr &req,
                                  std::function<void(const drg::HttpResponsePtr &)> &&callback,
                                  int userId) const {
    std::cout << "GET /" << userId << "/detailinfo" << std::endl;
    Json::Value json;
    json["userId"] = userId;
    json["detailinfo"] = true;
    json["status"] = "200";
    auto resp = drg::HttpResponse::newHttpJsonResponse(json);
    callback(resp);
}

void
api::v1::User::newUser(const drg::HttpRequestPtr &req, std::function<void(const drg::HttpResponsePtr &)> &&callback,
                       std::string &&userName) {
    std::cout << "GET /" << userName << std::endl;
    Json::Value json;
    json["userName"] = userName;
    json["status"] = "200";
    auto resp = drg::HttpResponse::newHttpJsonResponse(json);
    callback(resp);
}


int main() {
    const auto ip = "127.0.0.1";
    const auto port = 10010;
    std::cout << "Starting basic server on " << ip << ":" << port << std::endl;
    drg::app().setLogLevel(trantor::Logger::kDebug).addListener(ip, port).run();
}