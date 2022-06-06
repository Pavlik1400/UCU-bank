#include "credit.hpp"

namespace ucubank_api::v2 {
    Credit::Credit(const nlohmann::json &cnf) :
            APIBase(cnf),
            credit_client(cnf["credit"]["rpc_address"].get<str>(), cnf["credit"]["rpc_port"].get<int>()) {
        logger.info("Credit API v2 initialized");
    }

    jsonv Credit::create_h(const jsonv &req_json, jsonv &resp_json, const auth::AuthDU &privilege) {
        auto card = req_json["card_number"].as<str>();
        auto credit_type = req_json["type"].as<int>();
        auto amount = req_json["amount"].as<int>();
        auto user_id = privilege.cred;

        auto status = credit_client.create(user_id, card, credit_type, amount, privilege);
        if (status != credit::OK)
            return fail(credit::status_to_str(status), resp_json);

        return resp_json;
    }


    jsonv Credit::get_h(const jsonv &req_json, jsonv &resp_json, const auth::AuthDU &privilege) {
        str user_id;
        if (req_json["user_id"].empty())
            user_id = privilege.cred;
        else
            user_id = req_json["user_id"].as<str>();

        auto [status, credits] = credit_client.get_all(user_id, privilege);
        if (status != credit::OK)
            return fail(credit::status_to_str(status), resp_json);

        resp_json["credits"] = Json::Value{Json::arrayValue};
        for (auto const &cred: credits)
            resp_json["credits"].append(serialized_credit_t(cred));

        return resp_json;
    }

    jsonv Credit::finish_h(const jsonv &req_json, jsonv &resp_json, const auth::AuthDU &privilege) {
        auto id = req_json["id"].as<str>();
        auto user_id = privilege.cred;

        auto status = credit_client.finish_credit(user_id, id, privilege);
        if (status != credit::OK)
            return fail(credit::status_to_str(status), resp_json);

        return resp_json;
    }

    jsonv serialized_credit_t(const credit_t &cred) {
        Json::Value result{};
        if (!cred.id.empty()) result["id"] = cred.id;
        if (!cred.user_id.empty()) result["user_id"] = cred.user_id;
        if (!cred.card_number.empty()) result["card_number"] = cred.card_number;
        if (!cred.opening_date.empty()) result["opening_date"] = cred.opening_date;
        result["active"] = cred.active;
        result["original_balance"] = cred.original_balance;
        result["current_balance"] = cred.current_balance;
        result["percent"] = cred.percent;
        result["period"] = cred.period;
        return result;

    }

}
