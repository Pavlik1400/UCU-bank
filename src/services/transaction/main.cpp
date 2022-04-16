#include "transaction/service.hpp"
#include "service_tools/utils.hpp"


int main() {
    auto cnf = load_json_config("configs/main.json");
    Service service{cnf};
    service.run();
    return 0;
}