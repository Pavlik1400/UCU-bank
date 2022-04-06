#ifndef UCU_BANK_ACCOUNTAPI_HPP
#define UCU_BANK_ACCOUNTAPI_HPP

#include "Gateway.hpp"
#include "Account/include/constants.h"
#include "BasicMicroservice/include/BasicMicroservice.hpp"


namespace ucubank_api::v1 {

    class Account : public drogon::HttpController<Account> {
    public:
        METHOD_LIST_BEGIN
            //use METHOD_ADD to add your custom processing function here;
            METHOD_ADD(Account::create, "/create/", drg::Get, "LoginFilter");
        METHOD_LIST_END

        //your declaration of processing function maybe like this:
        void create(const drg::HttpRequestPtr &req, std::function<void(const drg::HttpResponsePtr &)> &&callback) const;

    public:
        Account() {
            std::cout << "Account constructor" << std::endl;
            LOG_DEBUG << "Account constructor!";
        }

    private:

    };
} // namespace api::v1

#endif //UCU_BANK_ACCOUNTAPI_HPP
