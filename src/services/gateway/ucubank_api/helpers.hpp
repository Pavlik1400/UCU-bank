#ifndef UCU_BANK_HELPERS_HPP
#define UCU_BANK_HELPERS_HPP

#include <string>
#include <vector>
#include <drogon/HttpController.h>

using str = std::string;

template<class T>
using vec = std::vector<T>;

namespace drg = drogon;

using drg_request = drg::HttpRequestPtr;
using resp_callback = std::function<void(const drg::HttpResponsePtr &)>;

using jsonv = Json::Value;

#ifdef DEBUG

#define DEBUG_TRY try {

#define DEBUG_CATCH } catch (const std::exception &exc) {\
std::cerr << "Caught exception: " << exc.what() << "\n";\
resp_json["status"] = 500;\
resp_json["message"] = std::string("Caught exception: ") + exc.what();\
callback(drg::HttpResponse::newHttpJsonResponse(resp_json));\
}


#define DEBUG_CATCH_RESP(resp_json) } catch (const std::exception &exc) {\
std::cerr << "Caught exception: " << exc.what() << "\n";\
resp_json["status"] = 500;\
resp_json["message"] = std::string("Caught exception: ") + exc.what();\
callback(drg::HttpResponse::newHttpJsonResponse(resp_json));\
}


#define IFDEBUG(code) \
    {                 \
        code;         \
    }

#else

#define IFDEBUG(code) \
    {                 \
        code;         \
    }

#define DEBUG_TRY
#define DEBUG_CATCH
#define DEBUG_CATCH_RESP(resp_json)
//#define IFDEBUG(code)

#endif //DEBUG

#endif //UCU_BANK_HELPERS_HPP
