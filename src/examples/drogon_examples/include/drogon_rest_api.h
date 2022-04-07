#ifndef UCUBANK_DROGON_REST_API_H
#define UCUBANK_DROGON_REST_API_H

#include <drogon/HttpController.h>

namespace drg = drogon;

namespace api::v1 {
    class User : public drogon::HttpController<User> {
    public:
        METHOD_LIST_BEGIN
            //use METHOD_ADD to add your custom processing function here;
            METHOD_ADD(User::getInfo, "/{id}", drg::Get);                  //path is /api/v1/User/{arg1}
            METHOD_ADD(User::getDetailInfo, "/{id}/detailinfo",drg::Get);  //path is /api/v1/User/{arg1}/detailinfo
            METHOD_ADD(User::newUser, "/{name}", drg::Post);               //path is /api/v1/User/{arg1}
        METHOD_LIST_END

        //your declaration of processing function maybe like this:
        void getInfo(const drg::HttpRequestPtr &req, std::function<void(const drg::HttpResponsePtr &)> &&callback,
                     int userId) const;

        void getDetailInfo(const drg::HttpRequestPtr &req, std::function<void(const drg::HttpResponsePtr &)> &&callback,
                           int userId) const;

        void newUser(const drg::HttpRequestPtr &req, std::function<void(const drg::HttpResponsePtr &)> &&callback,
                     std::string &&userName);

    public:
        User() {
            LOG_DEBUG << "User constructor!";
        }
    };
} // namespace api::v1

#endif //UCUBANK_DROGON_REST_API_H
