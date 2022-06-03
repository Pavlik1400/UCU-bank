#include "transaction/client.hpp"
#include "client/client.hpp"

namespace transaction {
    Client::Client(const nlohmann::json &cnf)
        : client::BasicClient(cnf["transaction"]["rpc_address"].get<std::string>()
            , cnf["transaction"]["rpc_port"].get<int>()
            , "TRANSACTION"
            ) {
    }

    status Client::create(const transaction_t &tran, const auth::AuthDU &priv) {
        return ver_connection(
            [&, this]() { return client->call("create", tran, priv).as<transaction::status>(); }
        );
    }

    tran_query_res Client::get(const trans_filter &filter, const auth::AuthDU &priv) {
        return ver_connection(
            [&, this]() { return client->call("get", filter, priv).as<tran_query_res>(); }
        );
    }
}