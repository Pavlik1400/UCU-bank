#ifndef UCU_BANK_CONFIGSERIALIZER_HPP
#define UCU_BANK_CONFIGSERIALIZER_HPP

#include <string>

#include <serdepp/serde.hpp>
#include <serdepp/adaptor/nlohmann_json.hpp>

template <typename T>
class ConfigSerializer {
public:
    static std::string serialize(const T& serialize_data);
    static T deserialize(const std::string& json_str);
};

template<typename T>
std::string ConfigSerializer<T>::serialize(const T &serialize_data) {
    auto json = serde::serialize<nlohmann::json>(serialize_data);
    std::string json_str = json.dump();
    return json_str;
}

template<typename T>
T ConfigSerializer<T>::deserialize(const std::string &json_str) {
    auto json = nlohmann::json::parse(json_str);
    auto config = serde::deserialize<T>(json);
    return config;
}


#endif //UCU_BANK_CONFIGSERIALIZER_HPP
