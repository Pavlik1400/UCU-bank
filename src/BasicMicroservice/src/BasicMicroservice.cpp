#include <csignal>
#include <iostream>

#include "BasicMicroservice.hpp"

std::function<void()> on_signal;
void signal_handler(int) {
    on_signal();
}

BasicMicroservice::BasicMicroservice(const std::string &broker_list_arg, const std::string &topic_name_arg, const ConfigStruct& config_struct_arg) :
                        kafka_config({
                            { "metadata.broker.list", broker_list_arg },
                            { "group.id", group_id },
                            { "enable.auto.commit", false }
                        }),
                        kafka_producer(kafka_config),
                        kafka_consumer(kafka_config),
                        kafka_builder(topic_name_arg),
                        kafka_dispatcher(kafka_consumer),
                        config_struct(config_struct_arg)
{

    kafka_consumer.subscribe({ topic_name_arg });
    on_signal = [&]() {
        kafka_dispatcher.stop();
    };
    signal(SIGINT, signal_handler);

}

void BasicMicroservice::run() {
    kafka_dispatcher.run(
            [&](cppkafka::Message msg) {
                std::string payload = msg.get_payload();
                kafka_consumer.commit(msg);
                auto deserialized = config_struct.deserialize(payload);
                receive_callback(deserialized);
            },
            [](cppkafka::Error error) {
                std::cout << "[+] Received error notification: " << error << std::endl;
            },
            [](cppkafka::ConsumerDispatcher::EndOfFile, const cppkafka::TopicPartition& topic_partition) {
                std::cout << "Reached EOF on partition " << topic_partition << std::endl;
            }
    );
}

void BasicMicroservice::receive_callback(BasicConfig &config) {
    std::cout << config.data << std::endl;
}

void BasicMicroservice::send(BasicConfig &config) {
    std::string line = config_struct.serialize(config);
    kafka_builder.payload(line);
    kafka_producer.produce(kafka_builder);
    kafka_producer.flush();
}
