#ifndef UCU_BANK_BASICMICROSERVICE_H
#define UCU_BANK_BASICMICROSERVICE_H

#include <string>
#include <cppkafka/configuration.h>
#include <cppkafka/consumer.h>
#include <cppkafka/producer.h>
#include <cppkafka/utils/consumer_dispatcher.h>

#include "ConfigStruct.hpp"

//static std::function<void()> on_signal;
//void signal_handler(int) {
//    on_signal();
//}

class BasicMicroservice {
public:
    BasicMicroservice(const std::string& broker_list_arg, const std::string& topic_name_arg, const ConfigStruct& config_struct_arg);
    void run();
    void send(BasicConfig& config);
    void receive_callback(BasicConfig& config);

private:
    std::string group_id = "microservice";

    cppkafka::Configuration kafka_config;
    cppkafka::Consumer kafka_consumer;
    cppkafka::Producer kafka_producer;
    cppkafka::MessageBuilder kafka_builder;
    cppkafka::ConsumerDispatcher kafka_dispatcher;

    ConfigStruct config_struct;
};


#endif //UCU_BANK_BASICMICROSERVICE_H
