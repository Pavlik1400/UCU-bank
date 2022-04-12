#include "UserMicroservice.h"


int main() {
    std::string redis_url = "tcp://localhost:6381";
    int port = 45646;

    auto user_microservice = UserMicroservice{port, redis_url};
    user_microservice.run();
}