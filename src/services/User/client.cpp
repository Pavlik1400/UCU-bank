#include "UserClient.h"


int main() {
    std::string addr = "127.0.0.1";
    int port = 45640;

    auto client = UserClient{addr, port};

}