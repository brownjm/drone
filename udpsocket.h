#pragma once

#include <string>
#include <vector>

class UDPSocket {
public:
    UDPSocket(const std::string& ip_address, int port);
    ~UDPSocket();

    void send(const std::string& message);
    std::string recv();

private:
    std::string ip_address; // ip addrs
    int port;
    int socket_handle;
    std::vector<unsigned char> recv_buffer;
};
