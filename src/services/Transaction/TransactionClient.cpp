#include "TransactionClient.hpp"

TransactionClient::TransactionClient(const nlohmann::json &cnf) :
        client(cnf["transaction"]["rpc_address"].get<std::string>(), cnf["transaction"]["rpc_port"].get<int>()) {
}

transaction::status TransactionClient::create(const Transaction &tran) {
    return client.call("create", tran).as<transaction::status>();
}

tran_query_res TransactionClient::get(const TransactionFilter &filter) {
    return client.call("get", filter).as<tran_query_res>();
}
