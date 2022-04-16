#include "gateway/account.hpp"
#include "basic/MessageSerializer.hpp"

ucubank_api::v1::Account::Account(const nlohmann::json &cnf) :
        accountClient(cnf["account"]["rpc_address"].get<std::string>(), cnf["account"]["rpc_port"].get<int>()) {
//    logger::init();
    logger.info("Account API initialized");
}


void ucubank_api::v1::Account::create(
        const drg::HttpRequestPtr &req,
        std::function<void(const drg::HttpResponsePtr &)> &&callback) {
    logger.debug("POST /ucubank_api/v1/account/create/");
    auto [success, req_json, resp_json] = prepare_json(req);
    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(req_json));

    DEBUG_TRY
        if (!verify_fields_present(req_json, resp_json, {"user_id", "account_type"}))
            return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));

        auto user_id = req_json["user_id"].as<std::string>();
        auto acc_type = req_json["account_type"].as<std::string>();

        auto create_status = accountClient.create(user_id, acc_type);

        // TODO: probably there will be more statuses
        if (create_status != account::OK) {
            if (create_status == account::CREATION_FAILED)
                return fail_response("db error", callback, resp_json, 500);
            return fail_response(account::status_to_str(create_status), callback, resp_json);
        }
        callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
    DEBUG_CATCH
}

void ucubank_api::v1::Account::info(const drogon::HttpRequestPtr &req,
                                       std::function<void(const drg::HttpResponsePtr &)> &&callback,
                                       const std::string &account_number) {

    logger.debug("GET /ucubank_api/v1/account/info/");
    auto [success, req_json, resp_json] = prepare_json(req);
    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(req_json));

    // TODO: check if user is allowed to get full information
    // if user is owner & resp[detailed] == true -> detailed=true, else false
    DEBUG_TRY
        auto[status, acc_info] = accountClient.get(account_number);
        if (status != account::OK) {
            if (status == account::GET_FAILED)
                return fail_response("db error", callback, resp_json, 500);
            return fail_response(account::status_to_str(status), callback, resp_json);
        }

        bool detailed;
        if (req_json["detailed"].empty()) detailed = false;
        else detailed = (req_json["detailed"].as<bool>());

        // TODO: find more clever serialization
        resp_json["info"] = Json::Value{};
        if (detailed) {
            resp_json["info"]["id"] = acc_info.id;
            resp_json["info"]["cvv"] = acc_info.cvv;
            resp_json["info"]["type"] = acc_info.type;
            resp_json["info"]["opening_date"] = acc_info.opening_date;
            resp_json["info"]["balance"] = acc_info.balance;
        }
        resp_json["info"]["user_id"] = acc_info.user_id;
        resp_json["info"]["number"] = acc_info.number;
        resp_json["info"]["active"] = acc_info.active;
        callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
    DEBUG_CATCH
}

void ucubank_api::v1::Account::remove(const drogon::HttpRequestPtr &req,
                                         std::function<void(const drg::HttpResponsePtr &)> &&callback,
                                         const std::string &account_number) {
    logger.debug("DELETE /ucubank_api/v1/accountemove/");
    auto [success, req_json, resp_json] = prepare_json(req);
    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(req_json));

    DEBUG_TRY
        auto status = accountClient.remove(account_number);
        if (status != account::OK) {
            return fail_response(account::status_to_str(status), callback, resp_json);
        }
        callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
    DEBUG_CATCH
}
