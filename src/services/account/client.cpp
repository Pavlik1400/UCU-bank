#include "AccountClient.h"


int main() {
    std::string addr = "127.0.0.1";
    int port = 45639;

    auto client = AccountClient{addr, port};
    client.create("0", "male");
    client.create("1", "female");

//    auto[status, responce] = client.get("6390721926535760");
//
//    std::cout << status << std::endl;
//    std::cout << responce << std::endl;
//
//    std::cout << client.transaction("9573202978162608", "6390721926535760", -323.122) << std::endl;
}