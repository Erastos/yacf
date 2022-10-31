#include "socket.h"


Socket::Socket(std::string addr, int port) {
    this->addr = addr;
    this->port = port;

    this->sockfd = -1;

    createSockets();
}

void Socket::createSockets() {

}
