#ifndef UCU_BANK_UTILS_HPP
#define UCU_BANK_UTILS_HPP

#include <serdepp/serde.hpp>
#include <serdepp/adaptor/nlohmann_json.hpp>
#include <string>
#include <rpc/msgpack.hpp>


nlohmann::json load_json_config(const std::string &path);

std::string cur_time_str();

std::string generate_current_datetime();

template<typename T>
struct ucu_optional {
public:
    ucu_optional();

    ucu_optional(T t) : has_value(true), value(std::move(t)) {}

    explicit operator bool() const {
        return has_value;
    }

public:
    bool has_value = false;
    T value;
    MSGPACK_DEFINE (has_value, value);

public:
    inline friend std::ostream &operator<<(std::ostream &os, const ucu_optional &opt) {
        if (!opt.has_value) os << "None";
        else os << opt.value;
        return os;
    }
};

template<typename T>
ucu_optional<T>::ucu_optional(): has_value(false) {}

#endif //UCU_BANK_UTILS_HPP
