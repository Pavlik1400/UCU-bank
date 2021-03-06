#ifndef UCU_BANK_TRANSACTION_CLIENT_HPP
#define UCU_BANK_TRANSACTION_CLIENT_HPP

#include "transaction/constants.hpp"
#include <nlohmann/json.hpp>
#include <rpc/client.h>
#include "client/client.hpp"
#include "auth/constants.hpp"

namespace transaction {
    class Client: public client::BasicClient {
    public:
        explicit Client(const nlohmann::json &cnf);
        transaction::status create(const transaction_t &tran, const auth::AuthDU &priv);
        tran_query_res get(const trans_filter &filter, const auth::AuthDU &priv);
    };
}

#endif //UCU_BANK_TRANSACTION_CLIENT_HPP
