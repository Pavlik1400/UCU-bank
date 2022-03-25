#include <iostream>
#include "BasicMicroservice.hpp"

class MyCustomConfig {
public:
    template<class Context>
    constexpr static auto serde(Context& context, MyCustomConfig& value) {
        using Self = MyCustomConfig;
        serde::serde_struct(context, value)
                .field(&Self::data, "data");
    }
    std::string data;
};

class MyCustomMicroservice: public BasicMicroservice<MyCustomConfig> {
    using BasicMicroservice<MyCustomConfig>::BasicMicroservice;

public:
    void receive_callback(const MyCustomConfig &config) override;
    void custom_start() override;
    void custom_finish() override;
};

void MyCustomMicroservice::receive_callback(const MyCustomConfig &config) {
    std::cout << "MyCustomMicroservice got message, data = " << config.data << std::endl;
}

void MyCustomMicroservice::custom_start() {
    std::cout << "MyCustomMicroservice start" << std::endl;
}

void MyCustomMicroservice::custom_finish() {
    std::cout << "MyCustomMicroservice finish" << std::endl;
}

int main() {
    std::string broker_list_arg = "localhost:9092";
    std::string topic_name_arg = "quickstart";

    auto my_custom_microservice = MyCustomMicroservice{broker_list_arg, topic_name_arg};
    my_custom_microservice.run();
}