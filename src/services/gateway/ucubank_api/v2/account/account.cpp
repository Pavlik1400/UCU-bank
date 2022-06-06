#include "account.hpp"
#include "basic/MessageSerializer.hpp"
#include "ucubank_api/helpers.hpp"
#include "ucubank_api/v2/user/user.hpp"


namespace ucubank_api::v2 {
    Account::Account(const nlohmann::json &cnf) :
            APIBase(cnf),
            account_client(cnf["account"]["rpc_address"].get<str>(), cnf["account"]["rpc_port"].get<int>()) {
        logger.info("Account API initialized");
    }


    jsonv Account::create_h(const jsonv &req_json, jsonv &resp_json, const auth::AuthDU &privilege) {
        auto user_id = req_json["user_id"].as<str>();
        auto acc_type = req_json["account_type"].as<str>();

        auto create_status = account_client.create(user_id, acc_type, privilege);
        if (create_status != account::OK) {
            if (create_status == account::CREATION_FAILED)
                return fail("db error", resp_json, 500);
            return fail(account::status_to_str(create_status), resp_json);
        }
        return resp_json;
    }

    jsonv Account::info_h(const jsonv &req_json, jsonv &resp_json, const auth::AuthDU &privilege) {
        auto account_number = req_json["account_number"].as<str>();
        auto [status, acc_info] = account_client.get(account_number, privilege);
        if (status != account::OK) {
            if (status == account::GET_FAILED)
                return fail("db error", resp_json, 500);
            return fail(account::status_to_str(status), resp_json);
        }
        resp_json["info"] = serialize_account_t(acc_info);
        return resp_json;
    }

    jsonv Account::remove_h(const jsonv &req_json, jsonv &resp_json, const auth::AuthDU &privilege) {
        auto account_number = req_json["account_number"].as<str>();
        auto status = account_client.remove(account_number, privilege);
        if (status != account::OK)
            return fail(account::status_to_str(status), resp_json);
        return resp_json;
    }

    jsonv Account::get_accs_h(const jsonv &req_json, jsonv &resp_json, const auth::AuthDU &privilege) {
        auto user_id = req_json["user_id"].as<str>();
        auto [status, accs] = account_client.get_all(user_id, privilege);
        if (status != account::OK)
            return fail(account::status_to_str(status), resp_json);

        resp_json["accounts"] = Json::Value{Json::arrayValue};
        for (auto const &acc: accs)
            resp_json["accounts"].append(serialize_account_t(acc));
        return resp_json;
    }

    jsonv Account::user_info_h(const jsonv &req_json, jsonv &resp_json, const auth::AuthDU &privilege) {
        auto acc_number = req_json["account_number"].as<str>();

        auto [status, user_info] = account_client.get_user(acc_number, privilege);
        if (status != account::OK)
            return fail(account::status_to_str(status), resp_json);
        resp_json["info"] = serialized_user_t(user_info);
        return resp_json;
    }


    Json::Value serialize_account_t(const account_t &acc_info) {
        Json::Value result{};
        if (!acc_info.id.empty()) result["id"] = acc_info.id;
        if (!acc_info.cvv.empty()) result["cvv"] = acc_info.cvv;
        if (!acc_info.opening_date.empty()) result["opening_date"] = acc_info.opening_date;
        if (!acc_info.type.empty()) result["type"] = acc_info.type;
        if (!acc_info.user_id.empty()) result["user_id"] = acc_info.user_id;
        if (!acc_info.number.empty()) result["number"] = acc_info.number;
        result["balance"] = acc_info.balance;
        result["active"] = acc_info.active;
        return result;
    }
}
