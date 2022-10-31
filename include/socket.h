#ifndef SOCKET_H_
#define SOCKET_H_

#include <string>

class Socket {
public:
    Socket(std::string addr, int port);
    void createSockets();

private:
    std::string addr;
    int port;
    int sockfd;
};


#endif // SOCKET_H_
