#ifndef UCU_BANK_DROGON_BASIC_H
#define UCU_BANK_DROGON_BASIC_H

#include <drogon/HttpSimpleController.h>

namespace drg = drogon;


class TestCtrl : public drogon::HttpSimpleController<TestCtrl> {
public:
    void asyncHandleHttpRequest(const drg::HttpRequestPtr &req,
                                std::function<void(const drg::HttpResponsePtr &)> &&callback) override;

    PATH_LIST_BEGIN
        PATH_ADD("/test", drg::Get);
    PATH_LIST_END
};

#endif //UCU_BANK_DROGON_BASIC_H
