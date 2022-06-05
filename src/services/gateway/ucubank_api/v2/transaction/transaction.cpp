#include "transaction.hpp"
#include "ucubank_api/helpers.hpp"


namespace ucubank_api::v2 {
    Transaction::Transaction(const nlohmann::json &cnf) :
            APIBase(cnf),
            transaction_client(cnf) {
        logger.info("Transaction service initialized");
    }

    jsonv Transaction::create_h(const jsonv &req_json, jsonv &resp_json, const auth::AuthDU &privilege) {
        auto status = transaction_client.create(deserialize_transaction_t(req_json), privilege);
        if (status != transaction::OK)
            return fail(transaction::status_to_str(status), resp_json);
        return resp_json;
    }

    jsonv Transaction::get_h(const jsonv &req_json, jsonv &resp_json, const auth::AuthDU &privilege) {
        auto account_number = req_json["account_number"].as<str>();

        auto [parse_status, filter] = deserialize_trans_filter(req_json, account_number);
        if (parse_status != transaction::OK) {
            return fail(transaction::status_to_str(parse_status), resp_json);
        }

        auto [status, ts] = transaction_client.get(filter, privilege);
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


    std::pair<transaction::status, trans_filter> deserialize_trans_filter(
            const Json::Value &req_json, const str &acc_number
    ) {
        trans_filter filter{
                acc_number,
                static_cast<unsigned long long>(req_json["limit"].as<int>()),
        };
        if (!req_json["from_date"].empty()) filter.from_date = req_json["from_date"].as<str>();
        if (!req_json["to_date"].empty()) filter.to_date = req_json["to_date"].as<str>();
        if (!req_json["min_amount"].empty()) filter.min_amount = req_json["min_amount"].as<double>();
        if (!req_json["max_amount"].empty()) filter.max_amount = req_json["max_amount"].as<double>();
        if (!req_json["description"].empty()) filter.description = req_json["description"].as<str>();
        if (!req_json["category"].empty()) {
            auto intcat = req_json["category"].as<int>();
            if (intcat < 0 || intcat > transaction::category::Count) {
                return {transaction::BAD_CATEGORY, {}};
            }
            filter.category = static_cast<transaction::category>(req_json["category"].as<int>());
        }
        return {transaction::OK, filter};
    }

    Json::Value serialize_transaction_t(const transaction_t &tran) {
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


    transaction_t deserialize_transaction_t(const Json::Value &json) {
        return {
                json["user_id"].as<str>(),
                json["from_acc_number"].as<str>(),
                json["to_acc_number"].as<str>(),
                json["description"].as<str>(),
                json["amount"].as<double>(),
                static_cast<transaction::category>(json["category"].as<int>())
        };
    }
}
