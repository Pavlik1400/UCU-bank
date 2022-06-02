#include "gateway/account.hpp"
#include "basic/MessageSerializer.hpp"
#include "user/constants.h"

ucubank_api::v1::Account::Account(const nlohmann::json &cnf) :
        account_client(cnf["account"]["rpc_address"].get<std::string>(), cnf["account"]["rpc_port"].get<int>()) {
//    logger::init();
    logger.info("Account API initialized");
}


void ucubank_api::v1::Account::create(
        const drg::HttpRequestPtr &req,
        std::function<void(const drg::HttpResponsePtr &)> &&callback) {
    logger.debug("POST /ucubank_api/v1/account/create/");
    auto [success, req_json, resp_json] = prepare_json(req);
    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));

    DEBUG_TRY
        if (!verify_fields_present(req_json, resp_json, {"user_id", "account_type"}))
            return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));

        auto user_id = req_json["user_id"].as<std::string>();
        auto acc_type = req_json["account_type"].as<std::string>();

        auto create_status = account_client.create(user_id, acc_type);

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
    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));

    DEBUG_TRY
        auto[status, acc_info] = account_client.get(account_number, {.data=user::privilege::SUPER});
        if (status != account::OK) {
            if (status == account::GET_FAILED)
                return fail_response("db error", callback, resp_json, 500);
            return fail_response(account::status_to_str(status), callback, resp_json);
        }
        // TODO: check if user is allowed to get full information about account
        resp_json["info"] = serialize_account_t(acc_info, true);
        callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
    DEBUG_CATCH
}

void ucubank_api::v1::Account::remove(const drogon::HttpRequestPtr &req,
                                         std::function<void(const drg::HttpResponsePtr &)> &&callback,
                                         const std::string &account_number) {
    logger.debug("DELETE /ucubank_api/v1/account/remove/");
    auto [success, req_json, resp_json] = prepare_json(req);
    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));

    DEBUG_TRY
        auto status = account_client.remove(account_number, {.data=user::privilege::SUPER});
        if (status != account::OK) {
            return fail_response(account::status_to_str(status), callback, resp_json);
        }
        callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
    DEBUG_CATCH
}

void ucubank_api::v1::Account::get_accs(const drogon::HttpRequestPtr &req,
                                        std::function<void(const drg::HttpResponsePtr &)> &&callback,
                                        const std::string &user_id) {
    logger.debug("POST /ucubank_api/v1/account/remove/");
    auto [success, req_json, resp_json] = prepare_json(req);
    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));

    DEBUG_TRY
        auto [status, accs] = account_client.get_all(user_id, {.data=user::privilege::SUPER});
        if (status != account::OK) {
            return fail_response(account::status_to_str(status), callback, resp_json);
        }
        resp_json["accounts"] = Json::Value{Json::arrayValue};
        for (auto const &acc: accs) {
            resp_json["accounts"].append(serialize_account_t(acc));
        }

        callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
    DEBUG_CATCH
}


Json::Value ucubank_api::v1::serialize_account_t(const account_t &acc_info, bool detailed) {
    // TODO: find more clever serialization
    Json::Value result{};
    if (detailed) {
        result["id"] = acc_info.id;
        result["cvv"] = acc_info.cvv;
        result["opening_date"] = acc_info.opening_date;
        result["balance"] = acc_info.balance;
    }
    result["type"] = acc_info.type;
    result["user_id"] = acc_info.user_id;
    result["number"] = acc_info.number;
    result["active"] = acc_info.active;
    return result;
}