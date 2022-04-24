#ifndef UCU_BANK_ACCOUNT_API_HPP
#define UCU_BANK_ACCOUNT_API_HPP

#include "api_utils.hpp"
#include "account/constants.h"
#include "account/client.h"
#include "basic/BasicMicroservice.hpp"


namespace ucubank_api::v1 {

    Json::Value serialize_account_t(const account_t &acc_info, bool detailed=true);

    class Account : public drogon::HttpController<Account, false> {
    public:
        METHOD_LIST_BEGIN
            METHOD_ADD(Account::create, "/create/", drg::Post);
            METHOD_ADD(Account::info, "/info/{account_number}", drg::Get);
            METHOD_ADD(Account::remove, "/remove/{account_number}", drg::Delete);
            METHOD_ADD(Account::get_accs, "/get_accounts/{user_id}", drg::Post);
        METHOD_LIST_END

        void create(const drg::HttpRequestPtr &req, std::function<void(const drg::HttpResponsePtr &)> &&callback);

        void info(const drg::HttpRequestPtr &req, std::function<void(const drg::HttpResponsePtr &)> &&callback,
                 const std::string &account_number);

        void remove(const drg::HttpRequestPtr &req, std::function<void(const drg::HttpResponsePtr &)> &&callback,
                 const std::string &account_number);

        void get_accs(const drg::HttpRequestPtr &req, std::function<void(const drg::HttpResponsePtr &)> &&callback,
                    const std::string &user_id);


    public:
        explicit Account(const nlohmann::json &cnf);

    private:
//        src::severity_logger<logging::trivial::severity_level> logger;
        GateWayLogger logger;
        account::Client account_client;
    };
} // namespace api::v1

#endif //UCU_BANK_ACCOUNT_API_HPP
