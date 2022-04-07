#include "Gateway.hpp"
#include <drogon/HttpAppFramework.h>
#include "BasicMicroservice/include/BasicMicroservice.hpp"


int main() {
    drg::app().loadConfigFile("gateway_config.json");
    std::cout << "Start gateway on 0.0.0.0:2020";
    rpc_clients_vec cv = {{"account", {"127.0.0.1", 45035}}};
    auto AccountAPIPtr=std::make_shared<AccountAPI>("hello world");
    drg::app().run();
    return 0;
}
