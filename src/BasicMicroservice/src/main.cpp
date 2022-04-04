#include <iostream>
#include "BasicMicroservice.hpp"

class MyCustomMicroservice : public BasicMicroservice {
    using BasicMicroservice::BasicMicroservice;

public:
    void custom_start() override;

    void custom_finish() override;

    ~MyCustomMicroservice() override;

private:
    std::string first_call(const std::string &some_str);

    void set_str(const std::string &some_str);

    std::string sub_call();

    std::string aaa_str = "qwert";
};

std::string MyCustomMicroservice::first_call(const std::string &some_str) {
    std::cout << "Calling first_call" << std::endl << std::endl;
    std::cout << rpc_clients.at("first-client").call("sub_call").as<std::string>() << std::endl;
    rpc_clients.at("first-client").call("set_str", some_str);
    std::cout << rpc_clients.at("first-client").call("sub_call").as<std::string>() << std::endl;

    return "fully done";
}

void MyCustomMicroservice::set_str(const std::string &some_str) {
    std::cout << "Calling set_str" << std::endl << std::endl;
    aaa_str = some_str;
}

std::string MyCustomMicroservice::sub_call() {
    std::cout << "Calling sub_call" << std::endl << std::endl;
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::string now_time_str = std::ctime(&now_time);
    return now_time_str + aaa_str;
}


void MyCustomMicroservice::custom_start() {
    rpc_server.bind("first_call", [&](const std::string &some_str) { return this->first_call(some_str); });
    rpc_server.bind("set_str", [&](const std::string &some_str) { return this->set_str(some_str); });
    rpc_server.bind("sub_call", [&]() { return this->sub_call(); });
    MLOG_TRACE << "MyCustomMicroservice start trace";
    MLOG_DEBUG << "MyCustomMicroservice start debug";
    MLOG_INFO << "MyCustomMicroservice start info";
    MLOG_WARNING << "MyCustomMicroservice start warning";
    MLOG_ERROR << "MyCustomMicroservice start error";
    MLOG_FATAL << "MyCustomMicroservice start fatal";

    MLOG_TRACE << "MyCustomMicroservice start trace";
    MLOG_DEBUG << "MyCustomMicroservice start debug";
    MLOG_INFO << "MyCustomMicroservice start info";
    MLOG_WARNING << "MyCustomMicroservice start warning";
    MLOG_ERROR << "MyCustomMicroservice start error";
    MLOG_FATAL << "MyCustomMicroservice start fatal";
}

void MyCustomMicroservice::custom_finish() {
    LOG(debug) << "MyCustomMicroservice finish" << std::endl;
}

MyCustomMicroservice::~MyCustomMicroservice() = default;

int main(int argc, char *argv[]) {
    if (argc > 1) {
        std::vector<std::pair<std::string, std::pair<std::string, unsigned short>>> clients = {{"first-client", {"127.0.0.1", 45035}}};
        int port = 45034;
        std::string redis_url = "tcp://localhost:6379";

        auto my_custom_microservice = MyCustomMicroservice{clients, port, redis_url};
        my_custom_microservice.run();
    } else {
        std::vector<std::pair<std::string, std::pair<std::string, unsigned short>>> clients = {};
        int port = 45035;
        std::string redis_url = "tcp://localhost:6379";

        auto my_custom_microservice = MyCustomMicroservice{clients, port, redis_url};
        my_custom_microservice.run();
    }
}