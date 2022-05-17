#include <csignal>
#include "basic/BasicMicroservice.hpp"
#include "service.h"

namespace notification {

    Service::Service(const nlohmann::json &cnf) : kafka_config({{"metadata.broker.list",
                                                                                       cnf["notification"]["broker_address"].get<std::string>() +
                                                                                       ":" +
                                                                                       cnf["notification"]["broker_port"].get<std::string>()},
                                                                {"group.id",           "ucu"},
                                                                {"enable.auto.commit", false}}), consumer(kafka_config),
                                                  builder(cnf["notification"]["topic"].get<std::string>()), cnf(cnf) {
        consumer.set_log_level(cppkafka::LogLevel::LogWarning);


    }

    bool Service::running = true;

    void Service::run() {
        start();
        while (running) {
            cppkafka::Message msg = consumer.poll();
            if (msg) {
                if (msg.get_error()) {
                    if (!msg.is_eof()) {
                        std::cout << "[+] Received error notification: " << msg.get_error() << std::endl;
                    }
                } else {
                    if (msg.get_key()) {
                        std::cout << msg.get_key() << " -> ";
                    }
                    std::cout << msg.get_payload() << std::endl;
                    consumer.commit(msg);
                }
            }
        }
        stop();
    }

    void Service::start() {
        signal(SIGINT, [](int) { running = false; });
        consumer.subscribe({builder.topic()});

    }

    void Service::stop() {

    }

}
