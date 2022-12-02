#include "udpsocket.h"
#include <atomic>
#include <stdexcept>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

constexpr std::size_t buffer_size = 1518;

UDPSocket::UDPSocket(const std::string& ip_address, int port)
    :ip_address{ip_address}, port{port}, socket_handle{socket(AF_INET, SOCK_DGRAM, 0)},
     recv_buffer(buffer_size) {
    if (socket_handle == -1) {
        std::string error_message{"UDPSocket(" + ip_address + ", " + std::to_string(port) + ") "};
        throw std::runtime_error(error_message + std::strerror(errno));
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(socket_handle, (struct sockaddr *)&address, sizeof(address)) == -1) {
        std::string error_message{"UDPSocket(" + ip_address + ", " + std::to_string(port) + ") "};
        throw std::runtime_error(error_message + std::strerror(errno));
    }
}

UDPSocket::~UDPSocket() {
    close(socket_handle);
}

void UDPSocket::send(const std::string& message) {
    // construct destination address
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip_address.data());
    address.sin_port = htons(port);

    ssize_t send_length = sendto(socket_handle, message.data(), message.size(), 0, (struct sockaddr *)&address, sizeof(address));
    
    if (send_length == -1) {
        std::string error_message{"UDPSocket(" + ip_address + ", " + std::to_string(port) + ")::send(\""};
        error_message += message + "\") ";
        throw std::runtime_error(error_message + std::strerror(errno));
    }
}

std::string UDPSocket::recv() {
    ssize_t recv_length = recvfrom(socket_handle, recv_buffer.data(), recv_buffer.size(), 0, nullptr, nullptr);
    if (recv_length == -1) {
        std::string error_message{"UDPSocket(" + ip_address + ", " + std::to_string(port) + ")::recv()"};
        throw std::runtime_error(error_message + std::strerror(errno));
    }

    std::string message{std::begin(recv_buffer), std::begin(recv_buffer) + recv_length};
    return message;
}
