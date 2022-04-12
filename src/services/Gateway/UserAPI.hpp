#ifndef UCU_BANK_USERAPI_H
#define UCU_BANK_USERAPI_H

#include "api_utils.hpp"

namespace ucubank_api::v1 {

    class UserAPI : public drogon::HttpController<UserAPI> {
    public:
        METHOD_LIST_BEGIN
            //use METHOD_ADD to add your custom processing function here;
            METHOD_ADD(UserAPI::info, "/info/{login}", drg::Get);
            METHOD_ADD(UserAPI::login, "/login/{login}", drg::Get);
            METHOD_ADD(UserAPI::register_, "/register/{login}", drg::Post);
//            METHOD_ADD(UserAPI::remove, "/register/{login}", drg::Delete);
        METHOD_LIST_END

        //your declaration of processing function maybe like this:
        void info(const drg::HttpRequestPtr &req, std::function<void(const drg::HttpResponsePtr &)> &&callback,
                  const std::string &login) const;

        void login(const drg::HttpRequestPtr &req, std::function<void(const drg::HttpResponsePtr &)> &&callback,
                   const std::string &login) const;

        void register_(const drg::HttpRequestPtr &req, std::function<void(const drg::HttpResponsePtr &)> &&callback,
                       const std::string &login);

//        void remove(const drg::HttpRequestPtr &req, std::function<void(const drg::HttpResponsePtr &)> &&callback,
//                       const std::string &login);

    public:
        UserAPI() {
//            LOG_DEBUG << "User constructor!";
        }
    };
} // namespace api::v1

#endif //UCU_BANK_USERAPI_H
