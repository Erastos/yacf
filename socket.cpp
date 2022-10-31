#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>

#include "socket.h"


Socket::Socket(std::string addr, int port) {
    this->addr = addr;
    this->port = port;
    this->domain = AF_INET;

    this->sockfd = -1;

    createSockets();
}

void Socket::createSockets() {
    int domain = AF_INET;
    int type = SOCK_STREAM;

    this->sockfd = socket(domain, type, 0);
}

void Socket::start() {
    struct sockaddr_in addr;
    addr.sin_family = domain;
    addr.sin_port = htons(this->port);
    inet_pton(AF_INET, this->addr.data(), &addr.sin_addr);

    errno = 0;
    int con_succ = connect(this->sockfd, (struct sockaddr*)&addr, (socklen_t)sizeof(addr));
    if (con_succ == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }
}

std::string Socket::get(int num) {
    char val[num];
    bzero(val, num);
    read(this->sockfd, val, num-1);
    val[num-1] = '\0';
    return std::string(val);
}

void Socket::put(std::string buf) {
    const char* buf_c = buf.data();
    send(this->sockfd, buf_c, buf.size(), 0);
}
