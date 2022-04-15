#include "account/AccountMicroservice.h"


int main() {
    std::string redis_url = "tcp://localhost:6379";
    int port = 45639;

    auto account_microservice = AccountMicroservice{port, redis_url};
    account_microservice.run();
}