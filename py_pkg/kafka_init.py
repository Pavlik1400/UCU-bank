import shutil
import sys
from subprocess import run

from . import cmd_t_split, KAFKA_CREATE_TOPICS_CMD_T, KAFKA_SYSTEMD_MODULE_ENABLE_CMD

def init_kafka():
    if shutil.which("kafka-topics.sh") is None:
        print("Kafka installation not found, please, install it with your package manager", file=sys.stderr)
        return

    run(KAFKA_SYSTEMD_MODULE_ENABLE_CMD)
    run(cmd_t_split(KAFKA_CREATE_TOPICS_CMD_T, topic_name="quickstart", partition_num=3))
    run(cmd_t_split(KAFKA_CREATE_TOPICS_CMD_T, topic_name="quickstart-out", partition_num=3))
    print("Kafka configured")

