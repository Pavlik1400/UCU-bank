#include "Gateway.hpp"
#include <drogon/HttpAppFramework.h>

int main() {
    drg::app().loadConfigFile("gateway_config.json");
    LOG_DEBUG << "Start gateway on 0.0.0.0:2020";
    drg::app().run();
    return 0;
}
