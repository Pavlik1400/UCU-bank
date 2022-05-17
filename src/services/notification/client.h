#ifndef UCU_BANK_NOTIFICATION_CLIENT_H
#define UCU_BANK_NOTIFICATION_CLIENT_H
#include <string>
#include <cppkafka/configuration.h>
#include <cppkafka/consumer.h>
#include <cppkafka/producer.h>
#include <cppkafka/utils/consumer_dispatcher.h>

namespace notification {
    class Client {
    protected:
        cppkafka::Configuration config;
        cppkafka::Producer producer;
        cppkafka::MessageBuilder builder;
        std::string default_topic;


    public:
        Client(const std::string &broker, const std::string &topic);
        void send(const std::string &message);
        void send(const std::string &message, const std::string &topic);

    };
}
#endif //UCU_BANK_NOTIFICATION_CLIENT_H
