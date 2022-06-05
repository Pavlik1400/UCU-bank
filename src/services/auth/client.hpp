#pragma once

#ifndef UCU_BANK_AUTH_CLIENT_HPP
#define UCU_BANK_AUTH_CLIENT_HPP

#include "auth/constants.hpp"
#include <rpc/client.h>
#include <nlohmann/json.hpp>
#include "client/client.hpp"

namespace auth {

class Client: public client::BasicClient{
public:
    explicit Client(const nlohmann::json &cnf);

    std::pair<auth::status, AuthDU>
    tfa_pwd(const AuthDU & id_n_pwd);
    
    std::pair<auth::status, AuthDU>
    tfa_otp(const AuthDU & id_n_otp);
    
    std::pair<auth::status, AuthDU>
    sess_info(const AuthDU & tk_n_info);


    std::pair<auth::status, AuthDU>
    sess_end(const AuthDU & tk_n_info);
};

} //auth

#endif //UCU_BANK_AUTH_CLIENT_HPP  