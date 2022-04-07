#include <stdexcept>
#include <iostream>
#include <cppkafka/producer.h>
#include <cppkafka/configuration.h>

int main(int argc, char* argv[]) {
    std::string brokers = "localhost:9092";
    std::string topic_name = "quickstart";

    // Create a message builder for this topic
    cppkafka::MessageBuilder builder(topic_name);

    // Construct the configuration
    cppkafka::Configuration config = {
            { "metadata.broker.list", brokers }
    };

    // Create the producer
    cppkafka::Producer producer(config);

    std::cout << "Producing messages into topic " << topic_name << std::endl;

    // Now read lines and write them into kafka
    std::string line;
    while (getline(std::cin, line)) {
        // Set the payload on this builder
        builder.payload(line);

        // Actually produce the message we've built
        producer.produce(builder);
    }

    // Flush all produced messages
    producer.flush();
}