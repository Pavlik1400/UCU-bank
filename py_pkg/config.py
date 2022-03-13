import json

with open("config.json", encoding="UTF-8", mode="r") as _:
    DEPENDENCIES = json.load(_)["dependencies"]