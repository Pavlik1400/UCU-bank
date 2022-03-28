#include <iostream>
#include "BasicMicroservice.hpp"

class MyCustomMicroservice : public BasicMicroservice {
    using BasicMicroservice::BasicMicroservice;

public:
    void receive_callback(const nlohmann::json &config) override;

    void custom_start() override;

    void custom_finish() override;

};

void MyCustomMicroservice::receive_callback(const nlohmann::json &config) {
    std::cout << "MyCustomMicroservice got message, data = " << config.at("data") << std::endl;
}

void MyCustomMicroservice::custom_start() {
    std::cout << "MyCustomMicroservice start" << std::endl;

    nlohmann::json json_to_send = nlohmann::json{};
    json_to_send["out-data"] = "started-MyCustomMicroservice";
    std::string dst = "quickstart-out";
    BasicMicroservice::send_request(json_to_send, dst);
}

void MyCustomMicroservice::custom_finish() {
    std::cout << "MyCustomMicroservice finish" << std::endl;

    nlohmann::json json_to_send = nlohmann::json{};
    json_to_send["out-data"] = "finished-MyCustomMicroservice";
    std::string dst = "quickstart-out-1";
    send_request(json_to_send, dst);
}

int main() {
    std::string broker_list_arg = "localhost:9092";
    std::string topic_input_name_arg = "quickstart";

    auto my_custom_microservice = MyCustomMicroservice{broker_list_arg, topic_input_name_arg};
    my_custom_microservice.run();
}