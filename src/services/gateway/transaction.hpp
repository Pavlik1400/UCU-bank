#ifndef UCU_BANK_TRANSACTION_HPP
#define UCU_BANK_TRANSACTION_HPP

#include "gateway/api_utils.hpp"
#include "basic/BasicMicroservice.hpp"
#include "transaction/client.hpp"
#include "transaction/constants.hpp"

namespace ucubank_api::v1 {

    std::pair<transaction::status, TransactionFilter> json_to_tran_filter(
            const Json::Value &req_json, const std::string &acc_number
            );
    Json::Value tran_to_json(const Transfer &tran);

    class Transaction : public drogon::HttpController<Transaction, false> {
    public:
        METHOD_LIST_BEGIN
            METHOD_ADD(Transaction::create, "/create/", drg::Post);
            METHOD_ADD(Transaction::get, "/get/{account_number}", drg::Get);
        METHOD_LIST_END

        void create(const drg::HttpRequestPtr &req, std::function<void(const drg::HttpResponsePtr &)> &&callback);

        void get(const drg::HttpRequestPtr &req, std::function<void(const drg::HttpResponsePtr &)> &&callback,
                  const std::string &account_number);

    public:
        explicit Transaction(const nlohmann::json &cnf);

    private:
//        src::severity_logger<logging::trivial::severity_level> logger;
        GateWayLogger logger;
        transaction::Client transaction_client;

    };
}


#endif //UCU_BANK_TRANSACTION_HPP
