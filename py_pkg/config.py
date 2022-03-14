import json
from .port import OS_NAME

def list_to_dict(prss):
    return {prs["name"]: prs for prs in prss}

with open("config.json", encoding="UTF-8", mode="r") as _:
    _ = json.load(_)
    TRIPLET = _['triplet'] + "-" + OS_NAME
    DEPENDENCIES = _["dependencies"]

with open("CMakePresets.json", encoding="UTF-8", mode="r") as _:
    _ = json.load(_)
    CONFIG_PRESETS = list_to_dict(_["configurePresets"])
    BUILD_PRESETS = list_to_dict(_["buildPresets"])