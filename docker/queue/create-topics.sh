#! /bin/bash

add_topic() {
    kafka-topics.sh --bootstrap-server localhost:9092   \
                    --create                            \
                    --topic notification                \
                    --partitions 1                      \
                    --replication-factor 1
    echo CREATED_TOPIC::notification
}

add_topic&