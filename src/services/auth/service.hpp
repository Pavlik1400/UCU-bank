#ifndef UCU_BANK_AUTH_SERVICE_HPP
#define UCU_BANK_AUTH_SERVICE_HPP

#include "basic/BasicMicroservice.hpp"
#include "auth/constants.hpp"
#include "email/MailSender.h"
#include "user/client.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <optional>

namespace auth {

class Service: public BasicMicroservice {
public:
    Service(const nlohmann::json &cnf);

    void start() override;

    void finish() override;

    virtual ~Service();

    std::pair<auth::status, AuthDU>
    tfa_req_otp(const AuthDU & id_n_pwd);
    
    std::pair<auth::status, AuthDU>
    tfa_ver_otp(const AuthDU & id_n_otp);
    
    std::pair<auth::status, AuthDU>
    sess_info(const AuthDU & tk_n_info);

private:
    void
    register_methods();

    std::optional<std::string>
    send_otp(const std::string & otp,
        const std::string & email);

    bool
    store(const std::string & key,
        const std::string & val,
        const long & ttl
    );

private:
    bool mock;
    user::Client user;
    email::MailSender msender;
    boost::uuids::random_generator uuid_gen;
}; 
} //auth

#endif //UCU_BANK_AUTH_SERVICE_HPP