#ifndef UCU_BANK_BASICMICROSERVICE_H
#define UCU_BANK_BASICMICROSERVICE_H

#include <string>
#include <vector>
#include <unordered_map>

#include <nlohmann/json.hpp>
#include <sw/redis++/redis++.h>
#include <rpc/server.h>
#include <rpc/client.h>


class BasicMicroservice {
public:
    BasicMicroservice(const std::vector<std::pair<std::string, std::pair<std::string, unsigned short>>>& clients, int port, const std::string &redis_url);

    void run();

    virtual void custom_start();

    virtual void custom_finish();

    virtual ~BasicMicroservice();

protected:
    rpc::server rpc_server;
    std::unordered_map<std::string, rpc::client> rpc_clients{};
    sw::redis::Redis redis_client;
};


#endif //UCU_BANK_BASICMICROSERVICE_H
