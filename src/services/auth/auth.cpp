#include "auth/service.hpp"
#include "service_tools/utils.hpp"


int main() {
    auto cnf = load_json_config("configs/main.json");
    auth::Service(cnf).run();
    return 0;
}