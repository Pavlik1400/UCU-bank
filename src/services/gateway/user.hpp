#ifndef UCU_BANK_USERAPI_H
#define UCU_BANK_USERAPI_H

#include "gateway/api_utils.hpp"
#include "user/client.h"
#include "user/constants.h"
#include "auth/client.hpp"


namespace ucubank_api::v1 {

    Json::Value serialized_user_t(const user_t &user_info, bool detailed=true);
    user_t deserialize_user_t(const Json::Value &json);

    class User : public drogon::HttpController<User, false> {
    public:
        METHOD_LIST_BEGIN
            METHOD_ADD(User::info, "/info/", drg::Post);
            METHOD_ADD(User::login1, "/login1/", drg::Post);
            METHOD_ADD(User::login2, "/login2/", drg::Post);
            METHOD_ADD(User::register_, "/register/", drg::Post);
            METHOD_ADD(User::remove, "/remove/", drg::Delete);
        METHOD_LIST_END

        //your declaration of processing function maybe like this:
        void info(const drg::HttpRequestPtr &req, std::function<void(const drg::HttpResponsePtr &)> &&callback);

        void login1(const drg::HttpRequestPtr &req, std::function<void(const drg::HttpResponsePtr &)> &&callback);

        void login2(const drg::HttpRequestPtr &req, std::function<void(const drg::HttpResponsePtr &)> &&callback);

        void register_(const drg::HttpRequestPtr &req, std::function<void(const drg::HttpResponsePtr &)> &&callback);

        void remove(const drg::HttpRequestPtr &req, std::function<void(const drg::HttpResponsePtr &)> &&callback);

    public:
        explicit User(const nlohmann::json &cnf);

    private:
        GateWayLogger logger;
        user::Client user_client;
        auth::Client auth_client;

//        const std::vector<std::string> login_fields{"name", "phone_num", "hashed_password"};
        const std::vector<std::string> info_fields{"name", "phone_num", "hashed_password"};
        const std::vector<std::string> register_fields{
                "type",
                "name",
                "password",
                "date_of_birth",
                "phoneNo",
                "email",
                "address",
                "gende",
        };
    };
} // namespace api::v1

#endif //UCU_BANK_USERAPI_H
