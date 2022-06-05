#ifndef UCU_BANK_USER_HPP2
#define UCU_BANK_USER_HPP2

#include "ucubank_api/api_utils.hpp"
#include "ucubank_api/v2/api_base.hpp"
#include "ucubank_api/helpers.hpp"
#include "ucubank_api/filter/verify_json_body.hpp"

namespace ucubank_api::v2 {

    jsonv serialized_user_t(const user_t &user_info);

    user_t deserialize_user_t(const jsonv &json);


    class User : public drg::HttpController<User, false>, public APIBase {
    public:
        explicit User(const nlohmann::json &cnf);

    private:
        user::Client user_client;

    public:
        METHOD_LIST_BEGIN
            METHOD_ADD(User::login1, "/login1/", VERIFY_JSON_FILTER, drg::Post);
            METHOD_ADD(User::login2, "/login2/", VERIFY_JSON_FILTER, drg::Post);
            METHOD_ADD(User::reg, "/register/", VERIFY_JSON_FILTER, drg::Post);
            METHOD_ADD(User::info, "/info/", VERIFY_JSON_FILTER, drg::Post);
            METHOD_ADD(User::remove, "/remove/", VERIFY_JSON_FILTER, drg::Delete);
            METHOD_ADD(User::logout, "/logout/", VERIFY_JSON_FILTER, drg::Post);
        METHOD_LIST_END

        ADD_ROUTE_HANDLER(login1, LIST("phone_num", "password"), "POST ucubank_api/v2/usernew/login1/")

        ADD_ROUTE_HANDLER(login2, LIST("one_time_passwd", "otp_key"), "POST ucubank_api/v2/usernew/login2/")

        ADD_ROUTE_HANDLER(
                reg,
                LIST("type", "name", "password", "date_of_birth", "phoneNo", "email", "address", "gender"),
                "POST ucubank_api/v2/usernew/register/")

        ADD_ROUTE_HANDLER_AUTH(info, LIST("phone_num"), "POST ucubank_api/v2/usernew/info/")

        ADD_ROUTE_HANDLER_AUTH(remove, LIST("phoneNo"), "DELETE ucubank_api/v2/usernew/remove/")

        ADD_ROUTE_HANDLER_AUTH(logout, LIST(), "POST ucubank_api/v2/usernew/logout/")
    };
}


#endif //UCU_BANK_USER_HPP2
