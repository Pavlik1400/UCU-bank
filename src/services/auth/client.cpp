#include "auth/client.hpp"
#include <nlohmann/json.hpp>

namespace auth {

Client::Client(const nlohmann::json &cnf)
    : client(cnf["auth"]["rpc_address"].get<std::string>(), cnf["auth"]["rpc_port"].get<int>())
    {}

std::pair<auth::status, AuthDU>
Client::tfa_pwd(const AuthDU & id_n_pwd)
{
    return client.call("tfa_pwd", id_n_pwd).as<std::pair<auth::status, AuthDU>>();
}
    
std::pair<auth::status, AuthDU>
Client::tfa_otp(const AuthDU & id_n_otp)
{

    return client.call("tfa_otp", id_n_otp).as<std::pair<auth::status, AuthDU>>();
}
    
std::pair<auth::status, AuthDU>
Client::sess_info(const AuthDU & tk_n_info)
{
    return client.call("sess_info", tk_n_info).as<std::pair<auth::status, AuthDU>>();
}

} //auth