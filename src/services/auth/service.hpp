#ifndef UCU_BANK_AUTH_SERVICE_HPP
#define UCU_BANK_AUTH_SERVICE_HPP

#include "basic/BasicMicroservice.hpp"
#include "auth/constants.hpp"
#include "email/MailSender.h"
#include "user/client.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace auth {
class Service: public BasicMicroservice {
public:
    Service(const nlohmann::json &cnf);

    void start() override;

    void finish() override;

    virtual ~Service();

    std::pair<auth::status, std::string>
    log1(const std::string & name, 
        const std::string & phoneNo,
        const std::string & pswd);
    
    std::pair<auth::status, std::string>
    log2(const std::string & auth_id, 
        const std::string & secret);

private:
    void register_methods();
    std::optional<boost::uuids::uuid> send_secret(const boost::uuids::uuid & secret,
                     const std::string & email);
    bool hash_secret(const boost::uuids::uuid & auth_id,
                     const boost::uuids::uuid & secret);

private:
    user::Client user;
    email::MailSender msender;
    boost::uuids::random_generator uuid_gen;
}; 
} //auth

#endif //UCU_BANK_AUTH_SERVICE_HPP