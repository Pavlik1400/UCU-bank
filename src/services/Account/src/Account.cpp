#include "AccountMicroservice.h"


int main() {
    std::string broker_list_arg = "localhost:9092";
    std::string redis_url = "tcp://localhost:6379";
    std::string topic_input_name_arg = "quickstart";

    auto account_microservice = AccountMicroservice{broker_list_arg, topic_input_name_arg, redis_url};
    account_microservice.run();
}