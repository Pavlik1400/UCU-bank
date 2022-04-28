#include "transaction/client.hpp"
#include "client/client.hpp"

namespace transaction {
    Client::Client(const nlohmann::json &cnf)
        : client::BasicClient(cnf["transaction"]["rpc_address"].get<std::string>()
            , cnf["transaction"]["rpc_port"].get<int>()
            , "TRANSACTION"
            ) {
    }

    status Client::create(const transaction_t &tran) {
        return ver_connection(
            [&, this]() { return client->call("create", tran).as<transaction::status>(); }
        );
    }

    tran_query_res Client::get(const trans_filter &filter) {
        return ver_connection(
            [&, this]() { return client->call("get", filter).as<tran_query_res>(); }
        );
    }
}