#include "transaction.hpp"

ucubank_api::v1::Transaction::Transaction(const nlohmann::json &cnf) : transaction_client(cnf) {
    logger.info("Transaction service initialized");
}


void ucubank_api::v1::Transaction::create(const drogon::HttpRequestPtr &req,
                                          std::function<void(const drg::HttpResponsePtr &)> &&callback) {
    logger.debug("POST /ucubank_api/v1/transaction/create/");
    auto [success, req_json, resp_json] = prepare_json(req);
    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));

    DEBUG_TRY
        if (!verify_fields_present(req_json, resp_json, {"user_id", "from_acc_number", "to_acc_number",
                                                         "description", "amount", "category"}))
            return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
        auto status = transaction_client.create(deserialize_transaction_t(req_json));
        if (status != transaction::OK) {
            return fail_response(transaction::status_to_str(status), callback, resp_json);
        }
        callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
    DEBUG_CATCH
}

void ucubank_api::v1::Transaction::get(const drogon::HttpRequestPtr &req,
                                       std::function<void(const drg::HttpResponsePtr &)> &&callback,
                                       const std::string &account_number) {

    logger.debug("GET /ucubank_api/v1/transaction/get/");
    auto [success, req_json, resp_json] = prepare_json(req);
    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));

    DEBUG_TRY
        if (!verify_fields_present(req_json, resp_json, {"limit"}))
            return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
        auto [parse_status, filter] = deserialize_trans_filter(req_json, account_number);
        if (parse_status != transaction::OK) {
            return fail_response(transaction::status_to_str(parse_status), callback, resp_json);
        }

        auto [status, ts] = transaction_client.get(filter);
        if (status != transaction::OK) {
            return fail_response(transaction::status_to_str(status), callback, resp_json);
        }

        auto tran_list = Json::Value(Json::arrayValue);

        for (const auto &transfer: ts) {
            tran_list.append(serialize_transaction_t(transfer));
        }
        resp_json["transactions"] = tran_list;
        callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
    DEBUG_CATCH

}


std::pair<transaction::status, trans_filter> ucubank_api::v1::deserialize_trans_filter(
        const Json::Value &req_json, const std::string &acc_number
) {
    trans_filter filter{
            acc_number,
            static_cast<unsigned long long>(req_json["limit"].as<int>()),
    };
    // TODO: fix code dublication
    if (!req_json["from_date"].empty()) filter.from_date = req_json["from_date"].as<std::string>();
    if (!req_json["to_date"].empty()) filter.to_date = req_json["to_date"].as<std::string>();
    if (!req_json["min_amount"].empty()) filter.min_amount = req_json["min_amount"].as<double>();
    if (!req_json["max_amount"].empty()) filter.max_amount = req_json["max_amount"].as<double>();
    if (!req_json["description"].empty()) filter.description = req_json["description"].as<std::string>();
    if (!req_json["category"].empty()) {
        auto intcat = req_json["category"].as<int>();
        if (intcat < 0 || intcat > transaction::category::Count) {
            return {transaction::BAD_CATEGORY, {}};
        }
        filter.category = static_cast<transaction::category>(req_json["category"].as<int>());
    }
    return {transaction::OK, filter};
}

Json::Value ucubank_api::v1::serialize_transaction_t(const transaction_t &tran) {
    auto result = Json::Value{};
    result["from_acc_number"] = tran.from_acc_number;
    result["to_acc_number"] = tran.to_acc_number;
    result["description"] = tran.description;
    result["amount"] = tran.amount;
    result["category"] = static_cast<int>(tran.category);
    if (tran.date) {
        result["date"] = tran.date.value;
    }
    return result;
}


transaction_t ucubank_api::v1::deserialize_transaction_t(const Json::Value &json) {
    // TODO: find better deserealization
    return {
            json["user_id"].as<std::string>(),
            json["from_acc_number"].as<std::string>(),
            json["to_acc_number"].as<std::string>(),
            json["description"].as<std::string>(),
            json["amount"].as<double>(),
            static_cast<transaction::category>(json["category"].as<int>())
    };
}