#include "auth/client.hpp"
#include <nlohmann/json.hpp>

namespace auth {

Client::Client(const nlohmann::json &cnf)
    : client(cnf["auth"]["rpc_address"].get<std::string>(), cnf["auth"]["rpc_port"].get<int>())
    {}

std::pair<auth::status, std::string>
Client::log1(const std::string & phoneNo, const std::string & pswd)
{
    return client.call("log1", phoneNo, pswd).as<std::pair<auth::status, std::string>>();
}

std::pair<auth::status, std::string>
Client::log2(const std::string & auth_id, 
    const std::string & secret) 
{
    return client.call("log2", auth_id, secret).as<std::pair<auth::status, std::string>>();
}

} //auth