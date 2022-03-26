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

private:

};

void MyCustomMicroservice::receive_callback(const MyCustomConfig &config) {
    std::cout << "MyCustomMicroservice got message, data = " << config.data << std::endl;
}

void MyCustomMicroservice::custom_start() {
    std::cout << "MyCustomMicroservice start" << std::endl;

    auto conf_to_send = MyCustomConfig{};
    conf_to_send.data = "started-MyCustomMicroservice";
    MyCustomMicroservice::send(conf_to_send);
}

void MyCustomMicroservice::custom_finish() {
    std::cout << "MyCustomMicroservice finish" << std::endl;

    auto conf_to_send = MyCustomConfig{};
    conf_to_send.data = "finished-MyCustomMicroservice";
    MyCustomMicroservice::send(conf_to_send);
}

int main() {
    std::string broker_list_arg = "localhost:9092";
    std::string topic_input_name_arg = "quickstart";
    std::string topic_output_name_arg = "quickstart-out";

    auto my_custom_microservice = MyCustomMicroservice{broker_list_arg, topic_input_name_arg, topic_output_name_arg};
    my_custom_microservice.run();
}