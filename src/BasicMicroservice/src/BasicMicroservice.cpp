#include "BasicMicroservice.hpp"
#include "MessageSerializer.hpp"
#include "constants.hpp"


BasicMicroservice::BasicMicroservice(const uint16_t port, const std::string &redis_url) : rpc_server(port),
                                                                                          redis_client(redis_url) {
    logger::init();
}

void BasicMicroservice::run() {
    custom_start();
    rpc_server.run();
    custom_finish();
}


BasicMicroservice::~BasicMicroservice() = default;

// Override next methods to your implementation
void BasicMicroservice::custom_start() {
    std::cout << "Base microservice start" << std::endl;
}

void BasicMicroservice::custom_finish() {
    std::cout << "Base microservice finish" << std::endl;
}
