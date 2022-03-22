#include <iostream>
#include "BasicMicroservice.hpp"

int main() {
    std::string broker_list_arg = "localhost:9092";
    std::string topic_name_arg = "quickstart";
    ConfigStruct config_struct_arg;
    auto mcrsrvc = BasicMicroservice{broker_list_arg, topic_name_arg, config_struct_arg};
    mcrsrvc.run();
}