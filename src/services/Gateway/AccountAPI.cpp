#include "AccountAPI.hpp"
#include "MessageSerializer.hpp"

ucubank_api::v1::AccountAPI::AccountAPI(const nlohmann::json &cnf) :
        accountClient(cnf["account"]["rpc_address"].get<std::string>(), cnf["account"]["rpc_port"].get<int>()) {
//    logger::init();
    logger.info("Account API initialized");
}


void ucubank_api::v1::AccountAPI::create(
        const drg::HttpRequestPtr &req,
        std::function<void(const drg::HttpResponsePtr &)> &&callback) {
    logger.debug("POST /ucubank_api/v1/accountapi/create/");
    auto[json, success] = getJsonObjectSafe(req);
    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(*json));
    auto req_json = *json;

    auto resp_json = Json::Value{};
    resp_json["status"] = 200;

    DEBUG_TRY
        if (!verify_fields_present(req_json, resp_json, {"name", "account_type"}))
            return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));

        auto user_id = req_json["user_id"].as<std::string>();
        auto acc_type = req_json["account_type"].as<std::string>();

        auto create_status = accountClient.create(user_id, acc_type);

        // TODO: probably there will be more statuses
        if (create_status != account::OK) {
            logger.debug("status 400 (could not create account)");
            resp_json["status"] = 400;
            resp_json["message"] = "Error while creating account";
            return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
        }

        logger.debug("status 200");
        callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
    DEBUG_CATCH
}

void ucubank_api::v1::AccountAPI::info(const drogon::HttpRequestPtr &req,
                                       std::function<void(const drg::HttpResponsePtr &)> &&callback,
                                       const std::string &account_number) {

    logger.debug("GET /ucubank_api/v1/accountapi/info/");
    auto[json, success] = getJsonObjectSafe(req);
    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(*json));
    auto req_json = *json;

    auto resp_json = Json::Value{};
    resp_json["status"] = 200;


    // TODO: check if user is allowed to get full information
    // if user is owner & resp[detailed] == true -> detailed=true, else false
    DEBUG_TRY
        auto[status, acc_info] = accountClient.get(account_number);
        if (status != account::OK) {
            return fail_response(status == account::GET_FAILED ? "Error in db query" : "Invalid card number",
                                 callback, resp_json);
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
        logger.debug("status 200");
        callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
    DEBUG_CATCH
}

void ucubank_api::v1::AccountAPI::remove(const drogon::HttpRequestPtr &req,
                                         std::function<void(const drg::HttpResponsePtr &)> &&callback,
                                         const std::string &account_number) {
    logger.debug("DELETE /ucubank_api/v1/accountapi/remove/");
    auto[json, success] = getJsonObjectSafe(req);
    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(*json));
    auto resp_json = *json;

    DEBUG_TRY
        auto status = accountClient.remove(account_number);
        if (status == account::INVALID_CARD_NUMBER) {
            logger.debug("status 400 (invalid card number)");
            resp_json["status"] = 400;
            resp_json["message"] = "Invalid card number";
            return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
        }
        logger.debug("status 200");
        callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
    DEBUG_CATCH
}
