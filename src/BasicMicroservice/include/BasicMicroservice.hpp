#ifndef UCU_BANK_BASICMICROSERVICE_H
#define UCU_BANK_BASICMICROSERVICE_H

#include <string>
#include <csignal>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include <cppkafka/configuration.h>
#include <cppkafka/consumer.h>
#include <cppkafka/producer.h>
#include <cppkafka/utils/consumer_dispatcher.h>
#include <nlohmann/json.hpp>


class BasicMicroservice {
public:
    BasicMicroservice(const std::string &broker_list_arg, const std::string &topic_input_name_arg);

    void run();

    void send_request(const nlohmann::json &msg, const std::string &dst);

    void send_response(const nlohmann::json &msg);

    virtual void receive_callback(const nlohmann::json &msg);

    virtual void custom_start();

    virtual void custom_finish();

private:
    std::string group_id = "microservice";
    std::string topic_input_name;

    cppkafka::Configuration kafka_config_producer;
    cppkafka::Configuration kafka_config_consumer;
    cppkafka::Consumer kafka_consumer;
    cppkafka::Producer kafka_producer;
    cppkafka::MessageBuilder kafka_builder;

    boost::uuids::random_generator uuid_generator{};

    void basic_send(const std::string &msg, const std::string &dst);

    static bool finished;
    static void set_finish([[maybe_unused]] int signum);
};


#endif //UCU_BANK_BASICMICROSERVICE_H
