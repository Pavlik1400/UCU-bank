#include <csignal>
//#include <msgpack.hpp>
#include "notification/constants.h"
#include "service.h"
//#include <msgpack.hpp>


namespace notification {

    Service::Service(const nlohmann::json &cnf) : kafka_config({{"metadata.broker.list",
                                                                                             cnf["notification"]["broker_address"].get<std::string>() +
                                                                                             ":" +
                                                                                             cnf["notification"]["broker_port"].get<std::string>()},
                                                                {"group.id",                 "ucu"},
                                                                {"allow.auto.create.topics", true},
                                                                {"enable.auto.commit",       false}}),
                                                  consumer(kafka_config),
                                                  builder(cnf["notification"]["topic"].get<std::string>()),
                                                  mock(cnf["auth"]["mock_mail"]),
                                                  msender(mock),
                                                  account(cnf["account"]["rpc_address"].get<std::string>(),
                                                          cnf["account"]["rpc_port"].get<int>()),
                                                  user(cnf["user"]["rpc_address"].get<std::string>(),
                                                       cnf["user"]["rpc_port"].get<int>()),
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
        const auto &[email, body] = decompose(message);
        std::cout << email << "<>" << body << std::endl;
        msender.with_receiver(email).with_body(body).send();
    }

    std::pair<std::string, std::string> Service::decompose(const std::string &message) {
//        clmdep_msgpack::unpa()
        auto notification = clmdep_msgpack::unpack(message.data(), message.size()).get().as<notification_t>();
        return {resolve(notification.identifier, notification.type), notification.payload};
    }

    std::string Service::resolve_with_email(const std::string &identifier) {
        return identifier;
    }

    std::string Service::resolve_with_user_id(const std::string &identifier) {
        const auto &[status, info] = user.get<user::by::ID>(identifier);
        return info.email;
    }

    std::string Service::resolve_with_phone_number(const std::string &identifier) {
        const auto &[status, info] = user.get<user::by::PHONE_NO>(identifier);
        return info.email;
    }

    std::string Service::resolve_with_card_number(const std::string &identifier) {
        const auto &[status1, info1] = account.get(identifier);
        const auto &[status2, info2] = user.get<user::by::ID>(info1.user_id);
        return info2.email;
    }

    std::string Service::resolve(const std::string &identifier, const identifier_type &type) {
        return (this->*handlers[type])(identifier);
    }

}
