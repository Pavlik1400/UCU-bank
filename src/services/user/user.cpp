#include "user/service.h"
#include "service_tools/utils.hpp"

int main() {
    auto cnf = load_json_config("configs/main.json");
    user::Service(cnf).run();
    return 0;
}