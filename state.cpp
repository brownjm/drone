#include "udpsocket.h"
#include <iostream>

int main() {
    UDPSocket command{"192.168.10.1", 8889};
    UDPSocket state{"192.168.10.1", 8890};

    command.send("command");
    command.recv();

    std::cout << "Receive Tello State\n";
    while (true) {
        std::cout << state.recv();
    }
}
