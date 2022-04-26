#ifndef UCU_BANK_TRANSACTION_CLIENT_HPP
#define UCU_BANK_TRANSACTION_CLIENT_HPP

#include "transaction/constants.hpp"
#include <nlohmann/json.hpp>
#include <rpc/client.h>

namespace transaction {
    class Client {
    private:
        rpc::client client;
    public:
        explicit Client(const nlohmann::json &cnf);
        transaction::status create(const transaction_t &tran);
        tran_query_res get(const trans_filter &filter);
    };
}

#endif //UCU_BANK_TRANSACTION_CLIENT_HPP
