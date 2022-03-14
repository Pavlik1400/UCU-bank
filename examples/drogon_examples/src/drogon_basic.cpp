#include "drogon_basic.h"

void TestCtrl::asyncHandleHttpRequest(const drg::HttpRequestPtr &req,
                                      std::function<void(const drg::HttpResponsePtr &)> &&callback) {
    //write your application logic here
    auto resp = drg::HttpResponse::newHttpResponse();
    resp->setBody("<p>Hello, world!</p>");
    resp->setExpiredTime(0);
    callback(resp);
}

int main() {
    const auto ip = "127.0.0.1";
    const auto port = 10010;
    std::cout << "Starting basic server on " << ip << ":" << port << std::endl;
    drg::app().setLogLevel(trantor::Logger::kDebug).addListener(ip, port).run();
}