#include "account/client.h"
#include "service_tools/utils.hpp"


int main() {
    auto cnf = load_json_config("./configs/main.json");
    auto client = account::Client{cnf["account"]["rpc_address"].get<std::string>(),
                                  cnf["account"]["rpc_port"].get<int>()};
//    client.create("625fbadb4baea65e95093e92", "shmexy");
    client.transaction("6390721926535760", "9573202978162608", 10);
}