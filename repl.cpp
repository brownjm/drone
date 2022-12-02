#include "udpsocket.h"
#include <iostream>

int main() {
    std::cout << "UDPSocket echo test\n";
    
    std::string ip{"192.168.10.1"};
    int port{8889};
    UDPSocket socket{ip, port};

    while (true) {
        std::cout << "> ";
        std::string message;
        std::getline(std::cin, message);
        socket.send(message);
        std::cout << socket.recv() << '\n';
    }
}
