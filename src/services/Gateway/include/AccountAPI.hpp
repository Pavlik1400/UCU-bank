#ifndef UCU_BANK_ACCOUNTAPI_HPP
#define UCU_BANK_ACCOUNTAPI_HPP

#include "api_utils.hpp"
#include "Account/include/account_constants.h"
#include "BasicMicroservice/include/BasicMicroservice.hpp"
#include "rpc/client.h"



namespace ucubank_api::v1 {

    class AccountAPI : public drogon::HttpController<AccountAPI, false> {
    public:
        METHOD_LIST_BEGIN
            //use METHOD_ADD to add your custom processing function here;
            METHOD_ADD(AccountAPI::create, "/create/", drg::Post, "LoginFilter");
        METHOD_LIST_END

        void create(const drg::HttpRequestPtr &req, std::function<void(const drg::HttpResponsePtr &)> &&callback);

    public:
        AccountAPI(rpc_clients_vec &clients) {
            logger::init();
            for (auto &client_entry : clients) {
                rpc_clients.try_emplace(client_entry.first, client_entry.second.first, client_entry.second.second);
            }
            CUSTOM_LOG(logger, debug) << "AccountAPI is created";

        }

    private:
        src::severity_logger< logging::trivial::severity_level > logger;
        rpc_clients_map rpc_clients;
    };
} // namespace api::v1

#endif //UCU_BANK_ACCOUNTAPI_HPP
