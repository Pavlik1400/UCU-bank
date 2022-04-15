#include <drogon/HttpAppFramework.h>
#include "gateway/AccountAPI.hpp"
#include "gateway/UserAPI.hpp"
#include "service_tools/utils.hpp"


int main() {
    auto cnf = load_json_config("./configs/main.json");
    std::cout << "Start gateway on 0.0.0.0:2020" << std::endl;
    auto AccountAPIPtr = std::make_shared<ucubank_api::v1::AccountAPI>(cnf);
    auto UserAPIPtr = std::make_shared<ucubank_api::v1::UserAPI>(cnf);
    drg::app().loadConfigFile("gateway_config.json");
    drogon::app().registerController(AccountAPIPtr);
    drogon::app().registerController(UserAPIPtr);
    drg::app().run();
    return 0;
}
