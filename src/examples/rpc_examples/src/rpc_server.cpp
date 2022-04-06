#include <iostream>
#include <rpc/server.h>

class RPCServer {
public:
    RPCServer(): srv(45034) {
        srv.bind("hello", [&]() { return this->hello(); });
        srv.bind("get_a", [&]() { return this->get_a(); });
        srv.bind("set_a", [&](int a) { return this->set_a(a); });
    }

    std::string hello() {
        return "hello world";
    }

    int get_a() {
        return aaa;
    }

    void set_a(int a) {
        aaa = a;
    }

    void run() {
        srv.run();
    }

private:
    rpc::server srv;
    int aaa = 46;
};

int main() {
    auto aaaa = RPCServer{};
    aaaa.run();
}