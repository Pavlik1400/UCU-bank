#include "basic/MessageSerializer.hpp"

std::string MessageSerializer::serialize(const nlohmann::json &json) {
    std::string json_str = json.dump();
    return json_str;
}

nlohmann::json MessageSerializer::deserialize(const std::string &json_str) {
    auto json = nlohmann::json::parse(json_str);
    return json;
}