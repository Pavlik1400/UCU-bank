#ifndef UCU_BANK_API_UTLIS_HPP
#define UCU_BANK_API_UTLIS_HPP

#include <drogon/HttpController.h>
#include <tuple>

using str = std::string;

namespace drg = drogon;

std::pair<std::shared_ptr<Json::Value>, bool> getJsonObjectSafe(const drogon::HttpRequestPtr &req, int err_status = 400,
                                                                int ok_status = 200);

bool verify_fields_present(Json::Value &req_json, Json::Value &resp_json, const std::vector<std::string> &fields);

void fail_response(const std::string &msg, std::function<void(const drg::HttpResponsePtr &)> &callback,
                   Json::Value &resp_json, int status = 400);

std::tuple<bool, Json::Value, Json::Value> prepare_json(const drogon::HttpRequestPtr &req);

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

// TODO: decide if use it
#ifdef DEBUG

#define DEBUG_TRY try {

#define DEBUG_CATCH } catch (const std::exception &exc) {\
std::cerr << "Caught exception: " << exc.what() << std::endl;\
resp_json["status"] = 500;\
resp_json["message"] = std::string("Caught exception: ") + exc.what();\
callback(drg::HttpResponse::newHttpJsonResponse(resp_json));\
}

#else

#define DEBUG_TRY
#define DEBUG_CATCH

#endif //DEBUG



//#define TRY_CATCH_WRAPPER(code) try { \
//code                                  \
//} catch (const std::exception &exc) {\
//std::cerr << "Caught exception: " << exc.what() << std::endl;\
//resp_json["status"] = 500;\
//resp_json["message"] = std::string("Caught exception: ") + exc.what();\
//callback(drg::HttpResponse::newHttpJsonResponse(resp_json));\
//}

#endif //UCU_BANK_API_UTLIS_HPP
