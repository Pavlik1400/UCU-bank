#ifndef UCU_BANK_UTILS_HPP
#define UCU_BANK_UTILS_HPP

#include <serdepp/serde.hpp>
#include <serdepp/adaptor/nlohmann_json.hpp>
#include <string>
#include <rpc/msgpack.hpp>


nlohmann::json load_json_config(const std::string &path);

std::string cur_time_str();

template<typename T>
struct ucu_optional {
public:
    ucu_optional() = default;

    ucu_optional(T t) : has_value(true), value(std::move(t)) {}

    explicit operator bool() const {
        return has_value;
    }

public:
    bool has_value = false;
    T value;
    MSGPACK_DEFINE (has_value, value);
};

#endif //UCU_BANK_UTILS_HPP
