#ifndef UCU_BANK_NOTIFICATION_SERVICE_H
#define UCU_BANK_NOTIFICATION_SERVICE_H
#include <nlohmann/json.hpp>
#include <cppkafka/configuration.h>
#include <cppkafka/consumer.h>
#include <cppkafka/producer.h>
#include <cppkafka/utils/consumer_dispatcher.h>
#include "auth/email/MailSender.h"
#include "basic/logging.hpp"

namespace notification {
    class Service {

    private:
        cppkafka::Configuration kafka_config;
        cppkafka::Consumer consumer;
        cppkafka::MessageBuilder builder;
        src::severity_logger<logging::trivial::severity_level> lg;
        bool mock;
        email::MailSender msender;
        const nlohmann::json cnf;

        std::pair<std::string, std::string> decompose(const std::string &message);
        void process(const std::string &message);

    public:
        static bool running;

        explicit Service(const nlohmann::json &cnf);
        void run();
        void start();
        void stop();
    };
}

#endif //UCU_BANK_NOTIFICATION_SERVICE_H
