#ifndef UCU_BANK_AUTH_SERVICE_HPP
#define UCU_BANK_AUTH_SERVICE_HPP

#include "basic/BasicMicroservice.hpp"
#include "auth/constants.hpp"
#include "service_tools/macro.hpp"
#include "user/client.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "notification/client.h"
#include <optional>
#include <ostream>
#include <sstream>
#include <unistd.h>



namespace auth {
template<token_type T>
constexpr size_t value_size()
{
    if constexpr (T == OneTimePswd) return 3;
    else if constexpr (T == UserInfo) return 2;
    else return 0;
}

template<token_type T>
constexpr size_t value_ttl()
{
    if constexpr (T == OneTimePswd) return 600;
    else if constexpr (T == UserInfo) return 6000;
    else return 0;
}

template<typename T, size_t N>
inline std::string str_array_to_string(const std::array<T, N> & a) 
{
    if (a.empty()) return {};
    std::ostringstream oss;
    oss << a[0];
    auto end{a.end()};
    for(auto el{a.begin()+1}; el!=end; ++el) oss << "," << *el;
    oss << "]";
    return oss.str();
}


template<typename T, size_t N>
inline std::ostream &operator<<(std::ostream &os, const std::array<T, N> & a)
{
    return os << str_array_to_string(a);
}

class Service: public BasicMicroservice {
public:
    explicit Service(const nlohmann::json &cnf);

    void start() override;
    void finish() override;
    ~Service() override;

    std::pair<auth::status, AuthDU> tfa_req_otp(const AuthDU & id_n_pwd);
    std::pair<auth::status, AuthDU> tfa_ver_otp(const AuthDU & id_n_otp);
    std::pair<auth::status, AuthDU> sess_info(const AuthDU & tk_n_info);
    std::pair<auth::status, AuthDU> sess_end(const AuthDU &tk_);

private:
    void register_methods();
    std::optional<std::string> send_otp(const std::string & otp, const std::string & email);

    template <token_type T>
    void hash_store(const std::string & key, std::array<std::string, value_size<T>()> && vals)
    {
        CUSTOM_LOG(lg, info) << LOG_FUNC(Service::hash_store, T, key);
        CUSTOM_LOG(lg, info) << str_array_to_string(vals);
        std::ostringstream oss;
        oss << vals[0];
        auto end{vals.end()};
        for (auto val{vals.begin()+1}; val!=end; ++val) oss << sep << *val;
        std::cerr << "STORED: {" << oss.str() << "}" << std::endl;
        redis_client.setex(token_type_to_str(T)+key, value_ttl<T>(), oss.str());
    }
    
    template <token_type T>
    auto hash_retrieve(const std::string & key) -> decltype(std::optional<std::array<std::string, value_size<T>()>>{}) {
        CUSTOM_LOG(lg, info) << LOG_FUNC(Service::hash_retrieve, T, key);
        if (!value_size<T>()) return {};
        auto val{redis_client.get(token_type_to_str(T) + key)};
        if (!val) return {};
        redis_client.expire(token_type_to_str(T) + key, value_ttl<T>());
        std::vector<std::string> v;
        std::array<std::string, value_size<T>()> a;
        boost::split(v, *val, [](char c){return c == sep;});
        std::copy(v.begin(), v.end(), a.begin());
        return a;
    }

    template <token_type T>
    void hash_del(const std::string & key) {
        CUSTOM_LOG(lg, info) << LOG_FUNC(Service::hash_del, T, key);
        redis_client.del(token_type_to_str(T) + key);
    }
    

private:
    user::Client user;
    notification::Client notification;
    boost::uuids::random_generator uuid_gen;
}; 
} //auth

#endif //UCU_BANK_AUTH_SERVICE_HPP