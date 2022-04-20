#include "transaction/client.hpp"

namespace transaction {
    Client::Client(const nlohmann::json &cnf) :
            client(cnf["transaction"]["rpc_address"].get<std::string>(), cnf["transaction"]["rpc_port"].get<int>()) {
    }

    status Client::create(const Transfer &tran) {
        return client.call("create", tran).as<transaction::status>();
    }

    tran_query_res Client::get(const TransactionFilter &filter) {
        return client.call("get", filter).as<tran_query_res>();
    }
}