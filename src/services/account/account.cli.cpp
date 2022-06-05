#include "account/client.h"
#include "service_tools/utils.hpp"
#include "user/constants.h"


int main() {
    auto cnf = load_json_config("./configs/main.json");
    auto client = account::Client{cnf["account"]["rpc_address"].get<std::string>(),
                                  cnf["account"]["rpc_port"].get<int>()};
//    client.create("625f1fbcc33b376b0c2954e2", "regular");

    auto[status, usr] = client.get_user("625f1fbcc33b376b0c2954e2", {.data=user::privilege::SUPER});
    std::cout << usr << std::endl;
//    for (auto& account: accounts) {
//        std::cout << account << std::endl;
//
//    }
//    client.transaction("6390721926535760", "9573202978162608", 10);
}