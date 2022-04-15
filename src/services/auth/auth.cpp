#include <iostream>
#include "AccountClient.h"
#include "user/client.h"
#include "auth/service.hpp"
#include "auth/constants.hpp"
#include "service_tools/utils.hpp"


int main(void)
{
    auto cnf = load_json_config("configs/main.json");
    auth::Service(cnf).run(); 
    return 0;
}