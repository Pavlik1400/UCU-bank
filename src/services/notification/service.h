#ifndef UCU_BANK_NOTIFICATION_SERVICE_H
#define UCU_BANK_NOTIFICATION_SERVICE_H
#include <nlohmann/json.hpp>
#include <cppkafka/configuration.h>
#include <cppkafka/consumer.h>
#include <cppkafka/producer.h>
#include <cppkafka/utils/consumer_dispatcher.h>

namespace notification {
    class Service {

    private:
        cppkafka::Configuration kafka_config;
        cppkafka::Consumer consumer;
        cppkafka::MessageBuilder builder;
        const nlohmann::json cnf;

    public:
        static bool running;

        explicit Service(const nlohmann::json &cnf);
        void run();
        void start();
        void stop();
    };
}

#endif //UCU_BANK_NOTIFICATION_SERVICE_H
