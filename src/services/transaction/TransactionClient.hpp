#ifndef UCU_BANK_TRANSACTIONCLIENT_HPP
#define UCU_BANK_TRANSACTIONCLIENT_HPP

#include "transaction/TransactionMicroservice.hpp"
#include "transaction/transaction_constants.hpp"
#include "basic/BasicMicroservice.hpp"
#include <nlohmann/json.hpp>

class TransactionClient {
private:
    rpc::client client;
public:
    TransactionClient(const nlohmann::json &cnf);
    transaction::status create(const Transaction &tran);
    tran_query_res get(const TransactionFilter &filter);
};


#endif //UCU_BANK_TRANSACTIONCLIENT_HPP
