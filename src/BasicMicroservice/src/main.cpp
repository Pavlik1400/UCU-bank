#include <iostream>
#include "BasicMicroservice.hpp"

class BasicConfig {
public:
    template<class Context>
    constexpr static auto serde(Context& context, BasicConfig& value) {
        using Self = BasicConfig;
        serde::serde_struct(context, value)
                .field(&Self::data, "data");
    }
    std::string data;
};

int main() {
    std::string broker_list_arg = "localhost:9092";
    std::string topic_name_arg = "quickstart";

    auto mcrsrvc = BasicMicroservice<BasicConfig>{broker_list_arg, topic_name_arg};
    mcrsrvc.run();
}