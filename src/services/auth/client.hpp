#pragma once

#ifndef UCU_BANK_AUTH_CLIENT_HPP
#define UCU_BANK_AUTH_CLIENT_HPP

#include "basic/BasicMicroservice.hpp"
#include "constants.hpp"
#include <rpc/client.h>
#include <nlohmann/json.hpp>

namespace auth {

class Client {
private:
    rpc::client client;
public:
    Client(const nlohmann::json &cnf);
    std::pair<auth::status, std::string>
    log1(   const std::string & name, 
            const std::string & phoneNo,
            const std::string & pswd  );
    
    std::pair<auth::status, std::string>
    log2(   const std::string & auth_id, 
            const std::string & secret );
};

} //auth

#endif //UCU_BANK_AUTH_CLIENT_HPP  