#include "api_utils.hpp"

#include <utility>
#include "auth/constants.hpp"

namespace ucubank_api {
    bool verify_fields_present(Json::Value &req_json, Json::Value &resp_json, const std::vector<std::string> &fields) {
        for (const auto &field: fields) {
            if (req_json[field].empty()) {
                resp_json["status"] = 400;
                resp_json["message"] = "'" + field + "' field is is not present";
                return false;
            }
        }
        return true;
    }

    parsed_request_t parse_json(const drogon::HttpRequestPtr &req) {
        auto resp_json = Json::Value{};
        auto req_json_ptr = req->getJsonObject();
        resp_json["status"] = 200;
        return {true, std::move(*req_json_ptr), std::move(resp_json)};
    }

    parsed_request_t parse_json(const drogon::HttpRequestPtr &req, auth::Client &auth_client) {
        // 1. Parse json body from request
        auto [success, req_json, resp_json, _] = parse_json(req);
        if (req_json["token"].empty()) {
            resp_json["status"] = 401;
            resp_json["message"] = "token is required";
            return {false, std::move(req_json), std::move(resp_json), auth::AuthDU{}};
        }
        // 2. get user priveleges
        auto [status, auth_resp] = auth_client.sess_info({req_json["token"].as<std::string>(), ""});
        std::cout << "Auth sess_info status: " << status << ", auth response: " << auth_resp.cred << ", "
                  << auth_resp.data << std::endl;
        if (status != auth::status::OK) {
            resp_json["status"] = 403;
            resp_json["message"] = (status == auth::status::GET_FAILED) ? "Invalid token" : auth::status_to_str(status);
            return {false, std::move(req_json), std::move(resp_json), auth::AuthDU{}};
        }
        return {true, std::move(req_json), std::move(resp_json), auth_resp};
    }

    void fail_response(const std::string &msg, std::function<void(const drg::HttpResponsePtr &)> &callback,
                       Json::Value &resp_json, int status) {
        resp_json["status"] = status;
        resp_json["message"] = msg;
        return callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
    }

    jsonv fail(const str &msg, jsonv &resp_json, int status){
        resp_json["status"] = status;
        resp_json["message"] = msg;
        return resp_json;
    }
}

void GateWayLogger::debug(const std::string &str) {
    std::cout << GateWayLogger::dbg_clr << GateWayLogger::bold << "[DBG] " << str << GateWayLogger::reset << std::endl;
}

void GateWayLogger::info(const std::string &str) {
    std::cout << GateWayLogger::inf_clr << GateWayLogger::bold << "[INF] " << str << GateWayLogger::reset << std::endl;
}

void GateWayLogger::warning(const std::string &str) {
    std::cout << GateWayLogger::war_clr << GateWayLogger::bold << "[WAR] " << str << GateWayLogger::reset << std::endl;
}

void GateWayLogger::error(const std::string &str) {
    std::cout << GateWayLogger::err_clr << GateWayLogger::bold << "[ERR] " << str << GateWayLogger::reset << std::endl;
}

void GateWayLogger::fatal(const std::string &str) {
    std::cout << GateWayLogger::fat_clr << GateWayLogger::bold << "[FAT] " << str << GateWayLogger::reset << std::endl;
}

const std::string GateWayLogger::dbg_clr = "\e[34m";
const std::string GateWayLogger::inf_clr = "\e[32m";
const std::string GateWayLogger::war_clr = "\e[93m";
const std::string GateWayLogger::err_clr = "\e[91m";
const std::string GateWayLogger::fat_clr = "\e[41m";
const std::string GateWayLogger::bold = "\e[1m";
const std::string GateWayLogger::reset = "\e[0m";