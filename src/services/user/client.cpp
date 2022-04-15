#include "user/UserClient.h"


int main() {
    std::string addr = "127.0.0.1";
    int port = 45646;

    auto client = UserClient{addr, port};
    auto status = client.create({
        "0",
        "alpha female",
        "Masha",
        "password",
        "2945-05-08",
        "+390961234567",
        "m.halilei@ucu.edu.ua",
        "toilet",
        "tractor",
        "2020-05-05",
        });
    std::cout << static_cast<std::underlying_type_t<user::status>>(status) << std::endl;

}