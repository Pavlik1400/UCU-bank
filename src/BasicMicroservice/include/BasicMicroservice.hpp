#ifndef UCU_BANK_BASICMICROSERVICE_H
#define UCU_BANK_BASICMICROSERVICE_H

#include <string>
#include <csignal>
#include <cppkafka/configuration.h>
#include <cppkafka/consumer.h>
#include <cppkafka/producer.h>
#include <cppkafka/utils/consumer_dispatcher.h>

#include "ConfigSerializer.hpp"

// TODO: remove template
template<typename T>
class BasicMicroservice {
public:
    BasicMicroservice(const std::string &broker_list_arg, const std::string &topic_input_name_arg,
                      const std::string &topic_output_name_arg);

    [[noreturn]] void run();

    void send(const T &config);

    virtual void receive_callback(const T &config);

    virtual void custom_start();

    virtual void custom_finish();

private:
    std::string group_id = "microservice";

    cppkafka::Configuration kafka_config_producer;
    cppkafka::Configuration kafka_config_consumer;
    cppkafka::Consumer kafka_consumer;
    cppkafka::Producer kafka_producer;
    cppkafka::MessageBuilder kafka_builder;

    static bool finished;

    static void set_finish([[maybe_unused]] int signum);
};

template<typename T>
bool BasicMicroservice<T>::finished = false;

template<typename T>
BasicMicroservice<T>::BasicMicroservice(const std::string &broker_list_arg, const std::string &topic_input_name_arg,
                                        const std::string &topic_output_name_arg) :
        kafka_config_producer({
                                      {"metadata.broker.list", broker_list_arg},
                              }),
        kafka_config_consumer({
                                      {"metadata.broker.list", broker_list_arg},
                                      {"group.id",             group_id},
                                      {"enable.auto.commit",   false},
                              }),
        kafka_producer(kafka_config_producer),
        kafka_consumer(kafka_config_consumer),
        kafka_builder(topic_output_name_arg) {

    kafka_consumer.subscribe({topic_input_name_arg});
    signal(SIGINT, &BasicMicroservice<T>::set_finish);
}

template<typename T>
void BasicMicroservice<T>::run() {
    custom_start();

    while (!BasicMicroservice<T>::finished) {
        cppkafka::Message msg = kafka_consumer.poll();
        if (msg) {
            if (msg.get_error()) {
                if (!msg.is_eof()) {
                    std::cout << "[+] Received error notification: " << msg.get_error() << std::endl;
                }
            } else {
                std::string payload = msg.get_payload();
                kafka_consumer.commit(msg);
                try {
                    // TODO: send to callback json
                    auto deserialized = ConfigSerializer<T>::deserialize(payload);
                    receive_callback(deserialized);
                } catch (const std::exception &e) {
                    std::cout << e.what() << std::endl;
                }
            }
        }
    }

    custom_finish();
}

// TODO: add arg dest + overload with auto generated uuid
template<typename T>
void BasicMicroservice<T>::send(const T &config) {
    std::string line = ConfigSerializer<T>::serialize(config);
    kafka_builder.payload(line);
    kafka_producer.produce(kafka_builder);
    kafka_producer.flush();
}

template<typename T>
void BasicMicroservice<T>::set_finish(int signum) {
    BasicMicroservice<T>::finished = true;
}


// TODO: Override it with your implementation
// TODO: change type to json
template<typename T>
void BasicMicroservice<T>::receive_callback(const T &config) {
    std::cout << "BasicMicroservice got message" << std::endl;
}

// TODO: Override it with your implementation
template<typename T>
void BasicMicroservice<T>::custom_start() {
    std::cout << "Base microservice start" << std::endl;
}

// TODO: Override it with your implementation
template<typename T>
void BasicMicroservice<T>::custom_finish() {
    std::cout << "Base microservice finish" << std::endl;
}

#endif //UCU_BANK_BASICMICROSERVICE_H
