#ifndef SOCKET_H_
#define SOCKET_H_

#include <string>

class Socket {
public:
    Socket(std::string addr, int port);
    void createSockets();
    void start();
    std::string get(int num);
    void put(std::string buf);

private:
    std::string addr;
    int port;
    int sockfd;
    int domain;
};


#endif // SOCKET_H_
