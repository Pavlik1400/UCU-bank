#include <iostream>
#include "client.h"
#include "constants.h"

namespace notification {

    Client::Client(const std::string &broker, const std::string &topic) : config({{"metadata.broker.list", broker}}),
                                                                          producer(config), builder(topic),
                                                                          default_topic(topic) {
        producer.set_log_level(cppkafka::LogLevel::LogWarning);

    }

    void Client::send(const std::string &message) {
        try {
            builder.payload(message);
            producer.produce(builder);
            producer.flush();
        } catch (cppkafka::HandleException &exception) {
            std::cerr << exception.what() << std::endl;
        }

    }

    void Client::send(const std::string &message, const std::string &topic) {
        builder.topic(topic);
        send(message);
        builder.topic(default_topic);
    }
}
