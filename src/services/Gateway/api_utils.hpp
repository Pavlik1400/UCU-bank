#ifndef UCU_BANK_API_UTLIS_HPP
#define UCU_BANK_API_UTLIS_HPP

#include <drogon/HttpController.h>

using str = std::string;

namespace drg = drogon;

std::pair<std::shared_ptr<Json::Value>, bool> getJsonObjectSafe(const drogon::HttpRequestPtr &req, int err_status = 400,
                                                                int ok_status = 200);

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
