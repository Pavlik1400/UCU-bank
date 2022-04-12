#include "api_utils.hpp"
#include <drogon/HttpAppFramework.h>
#include "BasicMicroservice/include/BasicMicroservice.hpp"
#include "AccountAPI.hpp"
#include "service_tools/utils.hpp"


int main() {
    auto cnf = load_json_config("./configs/main.json");
    std::cout << "Start gateway on 0.0.0.0:2020" << std::endl;
    auto AccountAPIPtr = std::make_shared<ucubank_api::v1::AccountAPI>(cnf);
    drg::app().loadConfigFile("gateway_config.json");
    drogon::app().registerController(AccountAPIPtr);
    drg::app().run();
    return 0;
}
