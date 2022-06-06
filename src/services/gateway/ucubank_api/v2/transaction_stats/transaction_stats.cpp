#include "transaction_stats.hpp"

namespace ucubank_api::v2 {
    TransactionStats::TransactionStats(const nlohmann::json &cnf) :
            APIBase(cnf),
            transaction_client(cnf) {
        logger.info("TransactionStats API v2 initialized");
    }

    jsonv TransactionStats::create_h(const jsonv &req_json, jsonv &resp_json) {
        auto status = transaction_client.create(deserialize_transaction_t(req_json), {.data=user::privilege::SUPER});
        if (status != transaction::OK)
            return fail(transaction::status_to_str(status), resp_json);
        return resp_json;
    }

    jsonv TransactionStats::get_h(const jsonv &req_json, jsonv &resp_json) {
        auto account_number = req_json["account_number"].as<str>();

        auto [parse_status, filter] = deserialize_trans_filter(req_json, account_number);
        if (parse_status != transaction::OK) {
            return fail(transaction::status_to_str(parse_status), resp_json);
        }

        auto [status, ts] = transaction_client.get(filter, {.data=user::privilege::SUPER});
        if (status != transaction::OK) {
            return fail(transaction::status_to_str(status), resp_json);
        }

        auto tran_list = Json::Value(Json::arrayValue);

        for (const auto &transfer: ts) {
            tran_list.append(serialize_transaction_t(transfer));
        }
        resp_json["transactions"] = tran_list;
        return resp_json;

    }

}
