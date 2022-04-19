#ifndef UCU_BANK_TRANSACTION_CLIENT_HPP
#define UCU_BANK_TRANSACTION_CLIENT_HPP

#include "transaction/service.hpp"
#include "transaction/constants.hpp"
#include "basic/BasicMicroservice.hpp"
#include <nlohmann/json.hpp>

namespace transaction {
    class Client {
    private:
        rpc::client client;
    public:
        explicit Client(const nlohmann::json &cnf);
        transaction::status create(const Transaction &tran);
        tran_query_res get(const TransactionFilter &filter);
    };
}

#endif //UCU_BANK_TRANSACTION_CLIENT_HPP
