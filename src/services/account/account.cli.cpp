#include "account/client.h"
#include "service_tools/utils.hpp"


int main() {
    auto cnf = load_json_config("./configs/main.json");
    auto client = account::Client{cnf["account"]["rpc_address"].get<std::string>(),
                                  cnf["account"]["rpc_port"].get<int>()};
    client.create("625f1fbcc33b376b0c2954e2", "sexy");
}