#include <iostream>
//#include <msgpack.hpp>
#include "client.h"

namespace notification {

    Client::Client(const std::string &broker, const std::string &topic) : config({{"metadata.broker.list", broker}}),
                                                                          producer(config), builder(topic),
                                                                          default_topic(topic) {
        producer.set_log_level(cppkafka::LogLevel::LogWarning);

    }

    void Client::send(const notification_t &notification) {
        try {
            auto message = convert(notification);
            builder.payload(message);
            producer.produce(builder);
            producer.flush();
        } catch (cppkafka::HandleException &exception) {
            std::cerr << exception.what() << std::endl;
        }

    }

    void Client::send(const notification_t &notification, const std::string &topic) {
        builder.topic(topic);
        send(notification);
        builder.topic(default_topic);
    }

    std::string Client::convert(const notification_t &notification) {
        std::stringstream buffer{};
        clmdep_msgpack::pack(buffer, notification);
        return buffer.str();
    }
}
