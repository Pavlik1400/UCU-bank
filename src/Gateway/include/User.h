#ifndef UCU_BANK_USER_H
#define UCU_BANK_USER_H

#include "Gateway.h"

namespace ucubank_api::v1 {

    class User : public drogon::HttpController<User> {
    public:
        METHOD_LIST_BEGIN
        //use METHOD_ADD to add your custom processing function here;
        METHOD_ADD(User::info, "/info/{login}", drg::Get);
        METHOD_ADD(User::login, "/login/{login}", drg::Get);
        METHOD_ADD(User::register_, "/register/{login}", drg::Post);
        METHOD_LIST_END

        //your declaration of processing function maybe like this:
        void info(const drg::HttpRequestPtr &req, std::function<void(const drg::HttpResponsePtr &)> &&callback,
                  const std::string &login) const;

        void login(const drg::HttpRequestPtr &req, std::function<void(const drg::HttpResponsePtr &)> &&callback,
                   const std::string &login) const;

        void register_(const drg::HttpRequestPtr &req, std::function<void(const drg::HttpResponsePtr &)> &&callback,
                       const std::string &login);

    public:
        User() {
            LOG_DEBUG << "User constructor!";
        }
    };
} // namespace api::v1

#endif //UCU_BANK_USER_H
