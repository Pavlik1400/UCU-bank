#ifndef UCU_BANK_DROGON_BASIC_H
#define UCU_BANK_DROGON_BASIC_H

#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

class TestCtrl : public drogon::HttpSimpleController<TestCtrl> {
public:
    void
    asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) override;

    PATH_LIST_BEGIN
        PATH_ADD("/test", Get);
    PATH_LIST_END
};

#endif //UCU_BANK_DROGON_BASIC_H
