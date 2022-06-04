#include <drogon/HttpAppFramework.h>

#include "service_tools/utils.hpp"
#include "ucubank_api/v1/account/account.hpp"
#include "ucubank_api/v1/user/user.hpp"
#include "ucubank_api/v1/transaction/transaction.hpp"
#include "ucubank_api/v2/user/user.hpp"
#include "ucubank_api/v2/account/account.hpp"
#include "ucubank_api/v2/transaction/transaction.hpp"

namespace api = ucubank_api::v1;
namespace api2 = ucubank_api::v2;

int main() {
    auto cnf = load_json_config("./configs/main.json");

    auto gateway_cnf = load_json_config("./configs/gateway/gateway_config.json");
    auto gateway_address = gateway_cnf["listeners"][0]["address"].get<std::string>();
    auto gateway_port = gateway_cnf["listeners"][0]["port"].get<size_t>();
    std::cout << "Start gateway on " << gateway_address << ":" << gateway_port << std::endl;

    auto AccountAPIPtr = std::make_shared<api::Account>(cnf);
    auto UserAPIPtr = std::make_shared<api::User>(cnf);
    auto TransactionAPIPtr = std::make_shared<api::Transaction>(cnf);
    auto UserAPIPtr_v2 = std::make_shared<api2::User>(cnf);
    auto AccpountAPIPtr_v2 = std::make_shared<api2::Account>(cnf);
    auto TransactionAPIPtr_v2 = std::make_shared<api2::Transaction>(cnf);

    drg::app().loadConfigFile("./configs/gateway/gateway_config.json");
    drg::app().registerController(AccountAPIPtr);
    drg::app().registerController(UserAPIPtr);
    drg::app().registerController(TransactionAPIPtr);
    drg::app().registerController(UserAPIPtr_v2);
    drg::app().registerController(AccpountAPIPtr_v2);
    drg::app().registerController(TransactionAPIPtr_v2);

    // CORS
    drg::app().registerPostHandlingAdvice(
            [](const drg::HttpRequestPtr &req, const drg::HttpResponsePtr &resp) {
                resp->addHeader("Access-Control-Allow-Origin", "*");
            });
    drg::app().run();
    return 0;
}
