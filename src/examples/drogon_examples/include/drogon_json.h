#ifndef UCUBANK_DROGON_JSON_H
#define UCUBANK_DROGON_JSON_H

#include <drogon/HttpSimpleController.h>

namespace drg = drogon;

class JsonCtrl : public drg::HttpSimpleController<JsonCtrl> {
public:
    virtual void asyncHandleHttpRequest(const drg::HttpRequestPtr &req,
                                        std::function<void(const drg::HttpResponsePtr &)> &&callback) override;

    PATH_LIST_BEGIN
        //list path definitions here;
        PATH_ADD("/json", drg::Get);
    PATH_LIST_END
};


#endif //UCUBANK_DROGON_JSON_H
