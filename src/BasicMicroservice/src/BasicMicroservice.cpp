#include "BasicMicroservice.hpp"
#include "MessageSerializer.hpp"
#include "constants.hpp"


BasicMicroservice::BasicMicroservice(const std::vector<std::pair<std::string, std::pair<std::string, unsigned short>>>& clients,
                                     const int port, const std::string &redis_url) : rpc_server(port),
                                     redis_client(redis_url) {
    logger::init();
    for (auto &client_entry : clients) {
        rpc_clients.try_emplace(client_entry.first, client_entry.second.first, client_entry.second.second);
    }
}

void BasicMicroservice::run() {
    start();
    rpc_server.run();
    finish();
}


BasicMicroservice::~BasicMicroservice() = default;


// Override next methods to your implementation
void BasicMicroservice::start() {
    std::cout << "Base microservice start" << std::endl;
}

void BasicMicroservice::finish() {
    std::cout << "Base microservice finish" << std::endl;
}
