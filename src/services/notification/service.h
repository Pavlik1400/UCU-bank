#ifndef UCU_BANK_NOTIFICATION_SERVICE_H
#define UCU_BANK_NOTIFICATION_SERVICE_H

#include <map>
#include <nlohmann/json.hpp>
#include <cppkafka/configuration.h>
#include <cppkafka/consumer.h>
#include <cppkafka/producer.h>
#include <cppkafka/utils/consumer_dispatcher.h>
#include "notification/email/MailSender.h"
#include "notification/constants.h"
#include "account/client.h"
#include "user/client.h"
#include "basic/logging.hpp"

namespace notification {
    class Service {

    private:
        cppkafka::Configuration kafka_config;
        cppkafka::Consumer consumer;
        cppkafka::MessageBuilder builder;
        src::severity_logger <logging::trivial::severity_level> lg;
        bool mock;
        email::MailSender msender;
        account::Client account;
        user::Client user;
        const nlohmann::json cnf;
        std::map<identifier_type, std::string (Service::*)(
                const std::string &identifier)> handlers{
                {identifier_type::EMAIL,       &Service::resolve_with_email},
                {identifier_type::CARD_NUMBER, &Service::resolve_with_card_number},
                {identifier_type::USER_ID,     &Service::resolve_with_user_id},
                {identifier_type::PHONE_NO,    &Service::resolve_with_phone_number}};

        std::pair<std::string, std::string> decompose(const std::string &message);

        void process(const std::string &message);

        std::string resolve(const std::string &identifier, const identifier_type &type);

        std::string resolve_with_email(const std::string &identifier);

        std::string resolve_with_card_number(const std::string &identifier);

        std::string resolve_with_user_id(const std::string &identifier);

        std::string resolve_with_phone_number(const std::string &identifier);

    public:
        static bool running;

        explicit Service(const nlohmann::json &cnf);

        void run();

        void start();

        void stop();
    };
}

#endif //UCU_BANK_NOTIFICATION_SERVICE_H
