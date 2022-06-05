#ifndef UCU_BANK_API_BASE_HPP
#define UCU_BANK_API_BASE_HPP

#include "ucubank_api/api_utils.hpp"
#include "user/client.h"
#include "user/constants.h"
#include "auth/client.hpp"
#include "ucubank_api/helpers.hpp"
#include <functional>


#define LIST(...) {__VA_ARGS__}

#define ADD_ROUTE_HANDLER(NAME, REQUIRED_FIELDS, PATH)                      \
    Json::Value NAME##_h(const jsonv &req_json, jsonv &resp_json);              \
    inline void NAME(const drg_request &req, resp_callback &&callback) {        \
        jsonv resp_json{};                                                      \
        resp_json["status"] = 200;                                              \
        wrap_handler<false>([&](auto req) { return NAME##_h(req, resp_json); }, \
                    REQUIRED_FIELDS, PATH, req, std::move(callback));       \
    }

#define ADD_ROUTE_HANDLER_AUTH(NAME, REQUIRED_FIELDS, PATH)                                             \
    Json::Value NAME##_h(const jsonv &req_json, jsonv &resp_json, const auth::AuthDU &privilege);            \
    inline void NAME(const drg_request &req, resp_callback &&callback) {                                    \
        jsonv resp_json{};                                                                                  \
        resp_json["status"] = 200;                                                                          \
        wrap_handler<true>([&](auto req, auto priv) { return NAME##_h(req, resp_json, priv); },             \
            REQUIRED_FIELDS, PATH, req, std::move(callback));                                               \
    }

//#define ADD_

namespace ucubank_api::v2 {
    class APIBase {

    protected:
        GateWayLogger logger;
        auth::Client auth_client;

    public:
        explicit APIBase(const nlohmann::json &cnf);

    protected:

        template<bool authenticate, typename T>
        void
        wrap_handler(T inner_handler, const vec<str> &&required_fields, str &&path, const drg_request &req,
                     resp_callback &&callback) {
            IFDEBUG(logger.debug(path))

            parsed_request_t pj;
            DEBUG_TRY
                if constexpr(authenticate) pj = parse_json(req, auth_client);
                else pj = parse_json(req);
                if (!pj.success) return callback(drg::HttpResponse::newHttpJsonResponse(pj.resp_json));

                if (!verify_fields_present(pj.req_json, pj.resp_json, required_fields))
                    return callback(drg::HttpResponse::newHttpJsonResponse(pj.resp_json));

                if constexpr(authenticate) pj.resp_json = std::invoke(inner_handler, pj.req_json, pj.privileges);
                else pj.resp_json = std::invoke(inner_handler, pj.req_json);

                callback(drg::HttpResponse::newHttpJsonResponse(pj.resp_json));
            DEBUG_CATCH_RESP(pj.resp_json);
        }
    };
}


#endif //UCU_BANK_API_BASE_HPP
