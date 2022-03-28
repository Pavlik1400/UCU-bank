#include "BasicMicroservice.hpp"
#include "MessageSerializer.hpp"
#include "constants.hpp"


BasicMicroservice::BasicMicroservice(const std::string &broker_list_arg, const std::string &topic_input_name_arg) :
        kafka_config_producer({{"metadata.broker.list", broker_list_arg},}), kafka_config_consumer(
        {{"metadata.broker.list", broker_list_arg},
         {"group.id",             group_id},
         {"enable.auto.commit",   false},}), kafka_producer(kafka_config_producer),
        kafka_consumer(kafka_config_consumer), kafka_builder(topic_input_name_arg), topic_input_name(topic_input_name_arg) {

    kafka_consumer.subscribe({topic_input_name_arg});
    signal(SIGINT, &BasicMicroservice::set_finish);
}

bool BasicMicroservice::finished = false;

void BasicMicroservice::run() {
    custom_start();

    while (!BasicMicroservice::finished) {
        cppkafka::Message msg = kafka_consumer.poll();
        if (msg) {
            if (msg.get_error()) {
                if (!msg.is_eof()) {
                    std::cout << "[+] Received error notification: " << msg.get_error() << std::endl;
                }
            } else {
                std::string payload = msg.get_payload();
                kafka_consumer.commit(msg);
                try {
                    auto deserialized = MessageSerializer::deserialize(payload);
                    receive_callback(deserialized);
                } catch (const std::exception &e) {
                    std::cout << e.what() << std::endl;
                }
            }
        }
    }

    custom_finish();
    return;
}

void BasicMicroservice::send_request(const nlohmann::json &msg, const std::string &dst) {
    auto copy_msg = msg;

    copy_msg[constants::MESSAGE_KEY_DST] = topic_input_name;
    copy_msg[constants::MESSAGE_KEY_UUID] = boost::uuids::to_string(uuid_generator());
    copy_msg[constants::MESSAGE_KEY_TYPE] = constants::message_types::REQUEST;

    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    copy_msg[constants::MESSAGE_KEY_TIMESTAMP] = oss.str();

    std::string line = MessageSerializer::serialize(copy_msg);
    basic_send(line, dst);
}

void BasicMicroservice::send_response(const nlohmann::json &msg) {
    auto copy_msg = msg;
    std::string dst = msg.at(constants::MESSAGE_KEY_DST);

    copy_msg[constants::MESSAGE_KEY_TYPE] = constants::message_types::RESPONSE;
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    copy_msg[constants::MESSAGE_KEY_TIMESTAMP] = oss.str();

    std::string line = MessageSerializer::serialize(copy_msg);
    basic_send(line, dst);
}

void BasicMicroservice::basic_send(const std::string &msg, const std::string &dst) {
    kafka_builder.topic(dst);
    kafka_builder.payload(msg);
    kafka_producer.produce(kafka_builder);
    kafka_producer.flush();
}

void BasicMicroservice::set_finish(int signum) {
    BasicMicroservice::finished = true;
}

// Override next methods to your implementation
void BasicMicroservice::receive_callback(const nlohmann::json &config) {
    std::cout << "BasicMicroservice got message" << std::endl;
}

void BasicMicroservice::custom_start() {
    std::cout << "Base microservice start" << std::endl;
}

void BasicMicroservice::custom_finish() {
    std::cout << "Base microservice finish" << std::endl;
}
