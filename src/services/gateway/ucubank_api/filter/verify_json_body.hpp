#ifndef UCU_BANK_VERIFY_JSON_BODY_HPP
#define UCU_BANK_VERIFY_JSON_BODY_HPP

#include <drogon/HttpFilter.h>

const std::string VERIFY_JSON_FILTER = "VerifyJsonBody";

class VerifyJsonBody : public drogon::HttpFilter<VerifyJsonBody> {
public:
    void doFilter(const drogon::HttpRequestPtr &req,
                  drogon::FilterCallback &&fcb,
                  drogon::FilterChainCallback &&fccb) override;
};


#endif //UCU_BANK_VERIFY_JSON_BODY_HPP
