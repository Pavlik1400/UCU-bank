#ifndef UCU_BANK_FILTERS_H
#define UCU_BANK_FILTERS_H

#include "drogon/HttpFilter.h"

class LoginFilter : public drogon::HttpFilter<LoginFilter> {
public:
    void doFilter(const drogon::HttpRequestPtr &req,
                  drogon::FilterCallback &&fcb,
                  drogon::FilterChainCallback &&fccb) override;
};

#endif //UCU_BANK_FILTERS_H
