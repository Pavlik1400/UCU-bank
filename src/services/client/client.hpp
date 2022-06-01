#pragma once

#ifndef UCU_BANK_CLIENT_HPP
#define UCU_BANK_CLIENT_HPP

#include <rpc/client.h>
#include <rpc/msgpack.hpp>
#include <iostream>
#include <msgpack/x3_unpack.hpp>

namespace client {

class BasicClient {
public:
    BasicClient(std::string &&server_addr, int server_port, std::string &&client_name)
        : server_addr_{std::move(server_addr)}
        , server_port_{server_port}
        , client_name_{client_name}
    {

    }

protected: 
    rpc::client* client = nullptr;
    
    template <typename Callable>
    auto ver_connection (Callable closure) -> decltype(closure()) {
        if (nullptr == client
            || rpc::client::connection_state::connected != client->get_connection_state()) {
            for ( ;; ) {
                if (nullptr != client) {
                    delete client;
                    client = nullptr;

                }
                try {
                    client = new rpc::client(server_addr_, server_port_);
                    auto tm {client->get_timeout()};
                    client->set_timeout(timeout_);
                    break;
                } catch (...) {
                    std::cerr << "FAILED TO CONNECT TO " << client_name_ << " microservice :( " << std::endl;
                }
            }
        }
        return closure();
    }

private:
    const std::string server_addr_;
    const std::string client_name_;
    const int server_port_;
    const unsigned timeout_{500};
};

}; //client

#endif //UCU_BANK_CLIENT_HPP