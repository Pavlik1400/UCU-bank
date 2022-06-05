#ifndef UCU_BANK_CREDIT_API_HPP
#define UCU_BANK_CREDIT_API_HPP

#include "ucubank_api/api_utils.hpp"
#include "ucubank_api/helpers.hpp"
#include "ucubank_api/v2/api_base.hpp"
#include "credit/client.h"

namespace ucubank_api::v2 {
    jsonv serialized_credit_t(const credit_t &cred);

    class Credit: public drg::HttpController<Credit, false>, public APIBase {
    public:
        explicit Credit(const nlohmann::json &cnf);

    private:
        credit::Client credit_client;

    public:
        METHOD_LIST_BEGIN
            METHOD_ADD(Credit::create, "/create/", drg::Post, drg::Options);
            METHOD_ADD(Credit::get, "/get/", drg::Post, drg::Options);
            METHOD_ADD(Credit::finish, "/finish/", drg::Post, drg::Options);

        METHOD_LIST_END

        ADD_ROUTE_HANDLER_AUTH(create, LIST("card_number", "type", "amount"), "POST ucubank_api/v2/credit/create/")
        ADD_ROUTE_HANDLER_AUTH(get, LIST(), "POST ucubank_api/v2/credit/get/")
        ADD_ROUTE_HANDLER_AUTH(finish, LIST("id"), "POST ucubank_api/v2/credit/finish/")
    };


}

#endif //UCU_BANK_CREDIT_API_HPP
