#include <iostream>
#include "rpc/client.h"

int main() {
    rpc::client client("127.0.0.1", 45034);
    std::cout << client.call("hello").as<std::string>() << std::endl;
    std::cout << client.call("get_a").as<int>() << std::endl;
    client.call("set_a", 570);
    std::cout << client.call("get_a").as<int>() << std::endl;
    return 0;
}