#include "UserMicroservice.h"


int main() {
    std::string redis_url = "tcp://localhost:6379";
    int port = 45640;

    auto user_microservice = UserMicroservice{port, redis_url};
    user_microservice.run();
}