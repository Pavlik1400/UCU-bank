#include "account/AccountMicroservice.h"
#include "service_tools/utils.hpp"


int main() {
    auto cnf = load_json_config("./config/main.json");
    auto account_microservice = AccountMicroservice{cnf};
    account_microservice.run();
}