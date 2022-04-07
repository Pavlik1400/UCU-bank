#ifndef UCU_BANK_FILTERS_HPP
#define UCU_BANK_FILTERS_HPP

#include "drogon/HttpFilter.h"

class LoginFilter : public drogon::HttpFilter<LoginFilter> {
public:
    void doFilter(const drogon::HttpRequestPtr &req,
                  drogon::FilterCallback &&fcb,
                  drogon::FilterChainCallback &&fccb) override;
};

#endif //UCU_BANK_FILTERS_HPP
