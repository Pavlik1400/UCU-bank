#include "account/service.h"
#include "service_tools/utils.hpp"


int main() {
    auto cnf = load_json_config("./configs/main.json");
    account::Service{cnf}.run();
}