#ifndef UCU_BANK_API_UTLIS_HPP
#define UCU_BANK_API_UTLIS_HPP

#include <drogon/HttpController.h>
using str = std::string;

namespace drg = drogon;

std::pair<std::shared_ptr<Json::Value>, bool> getJsonObjectSave(const drogon::HttpRequestPtr &req);

#endif //UCU_BANK_API_UTLIS_HPP
