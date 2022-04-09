#ifndef UCU_BANK_BASICMICROSERVICE_H
#define UCU_BANK_BASICMICROSERVICE_H

#include <string>
#include <vector>
#include <unordered_map>

#include <nlohmann/json.hpp>
#include <sw/redis++/redis++.h>
#include <rpc/server.h>
#include <rpc/client.h>

#include "logging.hpp"


struct RpcServerAddress {
    std::string address;
    uint16_t port;
};

class BasicMicroservice {
public:
    BasicMicroservice(uint16_t port, const std::string &redis_url);

    void run();

    virtual void start() = 0;

    virtual void finish() = 0;


    virtual ~BasicMicroservice();

protected:
    rpc::server rpc_server;
    sw::redis::Redis redis_client;
    src::severity_logger<logging::trivial::severity_level> lg;
};


#endif //UCU_BANK_BASICMICROSERVICE_H
