#include "api_utils.hpp"

std::pair<std::shared_ptr<Json::Value>, bool> getJsonObjectSafe(const drg::HttpRequestPtr &req, int err_status,
                                                                int ok_status) {
    auto req_json_ptr = req->getJsonObject();
    if (!req_json_ptr) {
        auto resp_json = new Json::Value;
        (*resp_json)["status"] = err_status;
        (*resp_json)["msg"] = "Error while parsing json: " + req->getJsonError();
        return {std::make_shared<Json::Value>(resp_json), false};
    }
    (*req_json_ptr)["status"] = ok_status;
    return {req_json_ptr, true};
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