#include <iostream>
#include <string>

#include <sys/wait.h>
#include <memory>

#include "process.h"
#include "socket.h"

int main (int argc, char* argv[]) {
    setvbuf(stdout, NULL, _IONBF, 0);
    // Process Test Code

    // args.push_back("hello world");
    // std::string program = "/bin/sh";
    // std::vector<std::string> args;
    // std::unique_ptr<Process> process = std::make_unique<Process>(program, args);
    // process->start();
    // std::string a = process->get(100);
    // std::cout << "Contents: " << a << "\n";
    // std::string a = "ls -la\n";
    // process->send(a);
    // usleep(4000);
    // std::string b = process->get(1000);
    // std::cout << "Contents: " << b << '\n';
    // std::string c = "cat test.txt\n";
    // process->send(c);
    // usleep(4000);
    // std::string d = process->get(1000);
    // std::cout << "Contents: " << d << '\n';


    // Socket Test Code
    std::string addr = "127.0.0.1";
    int port = 9001;

    std::unique_ptr<Socket> sock = std::make_unique<Socket>(addr, port);
    sock->start();

    std::string msg = "Test";

    sock->put(msg);
    std::string a = sock->get(100);
    std::cout << "Output: " << a << '\n';
    return 0;
}
