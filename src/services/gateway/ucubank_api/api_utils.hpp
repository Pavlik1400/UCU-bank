#ifndef UCU_BANK_API_UTLIS_HPP
#define UCU_BANK_API_UTLIS_HPP

#include <drogon/HttpController.h>
#include <tuple>
#include "auth/client.hpp"
#include "ucubank_api/helpers.hpp"

namespace ucubank_api {
    struct parsed_request_t {
        bool success;
        Json::Value req_json;
        Json::Value resp_json;
        auth::AuthDU privileges;
    };

    bool verify_fields_present(Json::Value &req_json, Json::Value &resp_json, const std::vector<std::string> &fields);

    void fail_response(const str &msg, resp_callback &callback, Json::Value &resp_json, int status = 400);

    Json::Value fail(const str &msg, Json::Value &resp_json, int status = 400);

    parsed_request_t parse_json(const drg_request &req);

    parsed_request_t parse_json(const drg_request &req, auth::Client &auth_client);

}

class GateWayLogger {
public:
    void debug(const std::string &str);

    void info(const std::string &str);

    void warning(const std::string &str);

    void error(const std::string &str);

    void fatal(const std::string &str);

private:
    static const std::string dbg_clr;
    static const std::string inf_clr;
    static const std::string war_clr;
    static const std::string err_clr;
    static const std::string fat_clr;
    static const std::string bold;
    static const std::string reset;
};

#endif //UCU_BANK_API_UTLIS_HPP
