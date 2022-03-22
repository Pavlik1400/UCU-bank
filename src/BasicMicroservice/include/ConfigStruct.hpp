#ifndef UCU_BANK_CONFIGSTRUCT_HPP
#define UCU_BANK_CONFIGSTRUCT_HPP

#include <string>

#include <serdepp/serde.hpp>
#include <serdepp/adaptor/nlohmann_json.hpp>

class BasicConfig {
public:
    template<class Context>
    constexpr static auto serde(Context& context, BasicConfig& value) {
        using Self = BasicConfig;
        serde::serde_struct(context, value)
                .field(&Self::data, "data");
    }
    std::string data;
};

class ConfigStruct {
public:
    static std::string serialize(const BasicConfig& serialize_data);
    static BasicConfig deserialize(const std::string& json_str);
};

#endif //UCU_BANK_CONFIGSTRUCT_HPP
