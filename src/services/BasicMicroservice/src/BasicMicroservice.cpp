#include "BasicMicroservice.hpp"
#include "MessageSerializer.hpp"
#include "constants.hpp"


BasicMicroservice::BasicMicroservice(const int port, const std::string &redis_url) : rpc_server(port),
                                                                                          redis_client(redis_url) {
    logger::init();
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
