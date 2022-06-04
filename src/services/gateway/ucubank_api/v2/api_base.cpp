#include "api_base.hpp"


namespace ucubank_api::v2 {
    APIBase::APIBase(const nlohmann::json &cnf) :
            auth_client(cnf) {
    }

//    template<typename T>
//    api_handler
//    APIBase::wrap_handler(T inner_handler, const vec<str> &&required_fields, str &&path, bool authenticate) {
//        return [&, this](
//                drg_request &req,
//                resp_callback &&callback
//        ) {
//            IFDEBUG(logger.debug(path))
//
//            Json::Value resp_json;
//            DEBUG_TRY
//                if (authenticate) {
//                    auto [success, req_json, err_resp_json, privilege] = parse_json(req, auth_client);
//                    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(err_resp_json));
//                    resp_json = inner_handler(req_json, privilege);
//                } else {
//                    auto [success, req_json, err_resp_json] = parse_json(req);
//                    if (!success) return callback(drg::HttpResponse::newHttpJsonResponse(err_resp_json));
//                    resp_json = inner_handler(req_json);
//                }
//                callback(drg::HttpResponse::newHttpJsonResponse(resp_json));
//            DEBUG_CATCH
//        };
//    }
}
