#include <csignal>
#include "basic/BasicMicroservice.hpp"
#include "service.h"

namespace notification {

    Service::Service(const nlohmann::json &cnf) : kafka_config({{"metadata.broker.list",
                                                                                       cnf["notification"]["broker_address"].get<std::string>() +
                                                                                       ":" +
                                                                                       cnf["notification"]["broker_port"].get<std::string>()},
                                                                {"group.id",           "ucu"},
                                                                {"allow.auto.create.topics", true},
                                                                {"enable.auto.commit", false}}), consumer(kafka_config),
                                                  builder(cnf["notification"]["topic"].get<std::string>()),
                                                  mock(cnf["auth"]["mock_mail"]),
                                                  msender(mock),
                                                  cnf(cnf) {
        consumer.set_log_level(cppkafka::LogLevel::LogWarning);
        logger::init();


    }

    bool Service::running = true;

    void Service::run() {
        start();
        while (running) {
            cppkafka::Message msg = consumer.poll();
            if (msg) {
                CUSTOM_LOG(lg, debug) << "Got message";
                if (msg.get_error()) {
                    if (!msg.is_eof()) {
                        CUSTOM_LOG(lg, error) << msg.get_error();
                    }
                } else {
                    if (msg.get_key()) {
                        std::cout << msg.get_key() << " -> ";
                    }
                    process(msg.get_payload());
                    consumer.commit(msg);
                }
            }
        }
        stop();
    }

    void Service::start() {
        signal(SIGINT, [](int) { running = false; });
        consumer.subscribe({builder.topic()});
        msender.with_sender("ucu.bank.24@gmail.com").with_subject("Notification");
        CUSTOM_LOG(lg, info) << "Notification service started";

    }

    void Service::stop() {


    }

    void Service::process(const std::string &message) {
        CUSTOM_LOG(lg, debug) << "Message content: " + message;
        const auto&[email, body] = decompose(message);
        msender.with_receiver(email).with_body(body).send();
    }

    std::pair<std::string, std::string> Service::decompose(const std::string &message) {
        return {"tsapiv@ucu.edu.ua", message};
    }
}
