#ifndef UCU_BANK_MESSAGESERIALIZER_HPP
#define UCU_BANK_MESSAGESERIALIZER_HPP

#include <string>

#include <serdepp/serde.hpp>
#include <serdepp/adaptor/nlohmann_json.hpp>

class MessageSerializer {
public:
    static std::string serialize(const nlohmann::json &json);

    static nlohmann::json deserialize(const std::string &json_str);
};

template<typename T>
nlohmann::json struct_to_json(const T &serialize_data) {
    auto json = serde::serialize<nlohmann::json>(serialize_data);
    return json;
}

template<typename T>
T json_to_struct(const nlohmann::json &json) {
    auto config = serde::deserialize<T>(json);
    return config;
}


#endif //UCU_BANK_MESSAGESERIALIZER_HPP
