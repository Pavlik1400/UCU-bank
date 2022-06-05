#ifndef UCU_BANK_TRANSACTION_STATS_HPP
#define UCU_BANK_TRANSACTION_STATS_HPP


#include "ucubank_api/api_utils.hpp"
#include "transaction/client.hpp"
#include "transaction/constants.hpp"
#include "ucubank_api/v2/api_base.hpp"
#include "ucubank_api/v2/transaction/transaction.hpp"
#include "user/constants.h"

namespace ucubank_api::v2 {

    class TransactionStats : public drg::HttpController<TransactionStats, false>, public APIBase {
    public:
        explicit TransactionStats(const nlohmann::json &cnf);

    private:
        transaction::Client transaction_client;

    public:
        METHOD_LIST_BEGIN
            METHOD_ADD(TransactionStats::create, "/create/", drg::Post, drg::Options);
            METHOD_ADD(TransactionStats::get, "/get/{account_number}", drg::Post, drg::Options);
        METHOD_LIST_END

        ADD_ROUTE_HANDLER(create,
                               LIST("user_id", "from_acc_number", "to_acc_number", "description", "amount", "category"),
                               "POST /ucubank_api/v2/transactionstats/create/")

        ADD_ROUTE_HANDLER(get, LIST("account_number", "limit"), "POST /ucubank_api/v2/transactionstats/get/")

    };
}


#endif //UCU_BANK_TRANSACTION_STATS_HPP
