#include "service_tools/utils.hpp"
#include <drogon/HttpAppFramework.h>
#include "gateway/account.hpp"
#include "gateway/user.hpp"
#include "gateway/transaction.hpp"


int main() {
    auto cnf = load_json_config("./configs/main.json");
    std::cout << "Start gateway on 0.0.0.0:2020" << std::endl;
    auto AccountAPIPtr = std::make_shared<ucubank_api::v1::Account>(cnf);
    auto UserAPIPtr = std::make_shared<ucubank_api::v1::User>(cnf);
    auto TransactionAPIPtr = std::make_shared<ucubank_api::v1::Transaction>(cnf);
    drg::app().loadConfigFile("./configs/gateway/gateway_config.json");
    drogon::app().registerController(AccountAPIPtr);
    drogon::app().registerController(UserAPIPtr);
    drogon::app().registerController(TransactionAPIPtr);
    drogon::app().registerPostHandlingAdvice(
            [](const drogon::HttpRequestPtr &req, const drogon::HttpResponsePtr &resp) {
                resp->addHeader("Access-Control-Allow-Origin", "*");
            });
    drg::app().run();
    return 0;
}
