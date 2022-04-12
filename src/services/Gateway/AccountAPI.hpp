#ifndef UCU_BANK_ACCOUNTAPI_HPP
#define UCU_BANK_ACCOUNTAPI_HPP

#include "api_utils.hpp"
#include "account_constants.h"
#include "AccountClient.h"
#include "BasicMicroservice/include/BasicMicroservice.hpp"


namespace ucubank_api::v1 {

    class AccountAPI : public drogon::HttpController<AccountAPI, false> {
    public:
        METHOD_LIST_BEGIN
            //use METHOD_ADD to add your custom processing function here;
            METHOD_ADD(AccountAPI::create, "/create/", drg::Post);
            METHOD_ADD(AccountAPI::info, "/info/{account_number}", drg::Get);
            METHOD_ADD(AccountAPI::remove, "/remove/{account_number}", drg::Delete);

        METHOD_LIST_END

        void create(const drg::HttpRequestPtr &req, std::function<void(const drg::HttpResponsePtr &)> &&callback);

        void info(const drg::HttpRequestPtr &req, std::function<void(const drg::HttpResponsePtr &)> &&callback,
                 const std::string &account_number);

        void remove(const drg::HttpRequestPtr &req, std::function<void(const drg::HttpResponsePtr &)> &&callback,
                 const std::string &account_number);


    public:
        explicit AccountAPI(const nlohmann::json &cnf);

    private:
//        src::severity_logger<logging::trivial::severity_level> logger;
        GateWayLogger logger;
        AccountClient accountClient;
    };
} // namespace api::v1

#endif //UCU_BANK_ACCOUNTAPI_HPP
