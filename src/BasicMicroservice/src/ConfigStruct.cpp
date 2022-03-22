#include "ConfigStruct.hpp"

std::string ConfigStruct::serialize(const BasicConfig& serialize_data) {
    auto json = serde::serialize<nlohmann::json>(serialize_data);
    std::string json_str = json.dump();
    return json_str;
}

BasicConfig ConfigStruct::deserialize(const std::string &json_str) {
    auto json = nlohmann::json::parse(json_str);
    auto config = serde::deserialize<BasicConfig>(json);
    return config;
}
