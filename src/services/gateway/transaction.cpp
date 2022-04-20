#include "transaction.hpp"

void ucubank_api::v1::Transaction::create(const drogon::HttpRequestPtr &req,
                                          std::function<void(const drg::HttpResponsePtr &)> &&callback) {
    logger.debug("GET /ucubank_api/v1/account/info/");
    auto [success, req_json, resp_json] = prepare_json(req);
    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));

    DEBUG_TRY
        if (!verify_fields_present(req_json, resp_json, {"user_id", "from_acc_number", "to_acc_number",
                                                         "description", "amount", "category"}))
            return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
        // TODO: find better deserealization
        Transfer tran{
                req_json["user_id"].as<std::string>(),
                req_json["from_acc_number"].as<std::string>(),
                req_json["to_acc_number"].as<std::string>(),
                req_json["description"].as<std::string>(),
                req_json["amount"].as<double>(),
                static_cast<transaction::category>(req_json.as<int>())
        };

        auto status = transaction_client.create(tran);
        if (status != transaction::OK) {
            return fail_response(transaction::status_to_str(status), callback, resp_json);
        }
        callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
    DEBUG_CATCH
}

void ucubank_api::v1::Transaction::get(const drogon::HttpRequestPtr &req,
                                       std::function<void(const drg::HttpResponsePtr &)> &&callback,
                                       const std::string &account_number) {

}

ucubank_api::v1::Transaction::Transaction(const nlohmann::json &cnf) : transaction_client(cnf) {
    logger.info("Transaction service initialized");
}
