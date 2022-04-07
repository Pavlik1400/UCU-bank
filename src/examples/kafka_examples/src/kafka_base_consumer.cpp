#include <stdexcept>
#include <iostream>
#include <csignal>
#include <cppkafka/consumer.h>
#include <cppkafka/configuration.h>
#include <cppkafka/utils/consumer_dispatcher.h>

std::function<void()> on_signal;

void signal_handler(int) {
    on_signal();
}

int main(int argc, char* argv[]) {
    std::string brokers = "localhost:9092";
    std::string topic_name = "quickstart";
    std::string group_id = "base_consumer";

    // Construct the configuration
    cppkafka::Configuration config = {
            { "metadata.broker.list", brokers },
            { "group.id", group_id },
            // Disable auto commit
            { "enable.auto.commit", false }
    };

    // Create the consumer
    cppkafka::Consumer consumer(config);

    // Print the assigned partitions on assignment
    consumer.set_assignment_callback([](const cppkafka::TopicPartitionList& partitions) {
        std::cout << "Got assigned: " << partitions << std::endl;
    });

    // Print the revoked partitions on revocation
    consumer.set_revocation_callback([](const cppkafka::TopicPartitionList& partitions) {
        std::cout << "Got revoked: " << partitions << std::endl;
    });

    // Subscribe to the topic
    consumer.subscribe({ topic_name });

    std::cout << "Consuming messages from topic " << topic_name << std::endl;

    // Create a consumer dispatcher
    cppkafka::ConsumerDispatcher dispatcher(consumer);

    // Stop processing on SIGINT
    on_signal = [&]() {
        dispatcher.stop();
    };
    signal(SIGINT, signal_handler);

    // Now run the dispatcher, providing a callback to handle messages, one to handle
    // errors and another one to handle EOF on a partition
    dispatcher.run(
            // Callback executed whenever a new message is consumed
            [&](cppkafka::Message msg) {
                std::cout << "Instance " << argv[1] << " ";
                // Print the key (if any)
                if (msg.get_key()) {
                    std::cout << msg.get_key() << " -> ";
                }
                // Print the payload
                std::cout << msg.get_payload() << std::endl;
                // Now commit the message
                consumer.commit(msg);
            },
            // Whenever there's an error (other than the EOF soft error)
            [](cppkafka::Error error) {
                std::cout << "[+] Received error notification: " << error << std::endl;
            },
            // Whenever EOF is reached on a partition, print this
            [](cppkafka::ConsumerDispatcher::EndOfFile, const cppkafka::TopicPartition& topic_partition) {
                std::cout << "Reached EOF on partition " << topic_partition << std::endl;
            }
    );
}