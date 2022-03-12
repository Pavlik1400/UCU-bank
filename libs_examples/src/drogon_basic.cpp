#include "drogon_basic.h"

void TestCtrl::asyncHandleHttpRequest(const HttpRequestPtr &req,
                                      std::function<void(const HttpResponsePtr &)> &&callback) {
    //write your application logic here
    auto resp = HttpResponse::newHttpResponse();
    resp->setBody("<p>Hello, world!</p>");
    resp->setExpiredTime(0);
    callback(resp);
}

int main() {
    const auto ip = "127.0.0.1";
    const auto port = 10010;
    std::cout << "Starting basic server on " << ip << ":" << port << std::endl;
    app().setLogLevel(trantor::Logger::kDebug).addListener(ip, port).run();
}