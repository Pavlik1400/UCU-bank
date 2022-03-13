#include "drogon_json.h"

void JsonCtrl::asyncHandleHttpRequest(const drg::HttpRequestPtr &req,
                                      std::function<void(const drg::HttpResponsePtr &)> &&callback) {
    Json::Value ret;
    ret["message"] = "Hello, World!";
    auto resp = drg::HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
}

int main() {
    const auto ip = "127.0.0.1";
    const auto port = 10010;
    std::cout << "Starting basic server on " << ip << ":" << port << std::endl;
    drg::app().setLogLevel(trantor::Logger::kDebug).addListener(ip, port).run();
}