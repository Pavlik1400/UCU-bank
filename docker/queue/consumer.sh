#! /bin/bash

kafka-console-consumer.sh   --bootstrap-server localhost:9092   \
                            --topic notification                \
                            --from-beginning