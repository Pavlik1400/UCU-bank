#ifndef UCU_BANK_TRANSACTION_HPP2
#define UCU_BANK_TRANSACTION_HPP2

#include "ucubank_api/api_utils.hpp"
#include "transaction/client.hpp"
#include "transaction/constants.hpp"
#include "ucubank_api/v2/api_base.hpp"

namespace ucubank_api::v2 {

    std::pair<transaction::status, trans_filter> deserialize_trans_filter(
            const Json::Value &req_json, const std::string &acc_number
    );

    jsonv serialize_transaction_t(const transaction_t &tran);

    transaction_t deserialize_transaction_t(const jsonv &json);

    class Transaction : public drogon::HttpController<Transaction, false>, public APIBase {
    public:
        explicit Transaction(const nlohmann::json &cnf);

    private:
        transaction::Client transaction_client;

    public:
        METHOD_LIST_BEGIN
            METHOD_ADD(Transaction::create, "/create/", drg::Post, drg::Options);
            METHOD_ADD(Transaction::get, "/get/{account_number}", drg::Post, drg::Options);
        METHOD_LIST_END

        ADD_ROUTE_HANDLER_AUTH(create,
                               LIST("user_id", "from_acc_number", "to_acc_number", "description", "amount", "category"),
                               "POST /ucubank_api/v2/transaction/create/")

        ADD_ROUTE_HANDLER_AUTH(get, LIST("account_number", "limit"), "POST /ucubank_api/v2/transaction/get/")
//        void create(const drg::HttpRequestPtr &req, std::function<void(const drg::HttpResponsePtr &)> &&callback);
//
//        void get(const drg::HttpRequestPtr &req, std::function<void(const drg::HttpResponsePtr &)> &&callback,
//                 const std::string &account_number);

    };
}


#endif //UCU_BANK_TRANSACTION_HPP2
