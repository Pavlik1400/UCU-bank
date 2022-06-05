#ifndef UCU_BANK_ACCOUNT_API_HPP
#define UCU_BANK_ACCOUNT_API_HPP

#include "ucubank_api/api_utils.hpp"
#include "account/constants.h"
#include "account/client.h"
#include <nlohmann/json.hpp>
#include "ucubank_api/v2/api_base.hpp"

namespace ucubank_api::v2 {

    Json::Value serialize_account_t(const account_t &acc_info);

    class Account : public drogon::HttpController<Account, false>, public APIBase {
    public:
        explicit Account(const nlohmann::json &cnf);

    private:
        account::Client account_client;

    public:
        METHOD_LIST_BEGIN
            METHOD_ADD(Account::create, "/create/", drg::Post, drg::Options);
            METHOD_ADD(Account::info, "/info/", drg::Post, drg::Options);
            METHOD_ADD(Account::remove, "/remove/", drg::Delete, drg::Options);
            METHOD_ADD(Account::get_accs, "/get_accounts/", drg::Post, drg::Options);
            METHOD_ADD(Account::user_info, "/user_info/", drg::Post, drg::Options);
        METHOD_LIST_END

        ADD_ROUTE_HANDLER_AUTH(create, LIST("user_id", "account_type"),
                               "POST /ucubank_api/v2/account/create/")

        ADD_ROUTE_HANDLER_AUTH(info, LIST("account_number"), "POST /ucubank_api/v2/account/info/")

        ADD_ROUTE_HANDLER_AUTH(remove, LIST("account_number"), "POST /ucubank_api/v2/account/remove/")

        ADD_ROUTE_HANDLER_AUTH(get_accs, LIST("user_id"), "POST /ucubank_api/v2/account/get_accounts/")

        ADD_ROUTE_HANDLER_AUTH(user_info, LIST("account_number"), "POST /ucubank_api/v2/account/user_info/")

    };
} // namespace api::v1

#endif //UCU_BANK_ACCOUNT_API_HPP
