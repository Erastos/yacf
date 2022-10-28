#include "process.h"
#include <iostream>
#include <string>
#include <sys/wait.h>
#include <memory>

int main (int argc, char* argv[]) {
    setvbuf(stdout, NULL, _IONBF, 0);
    std::vector<std::string> args;
    // args.push_back("hello world");
    std::string program = "/bin/sh";
    std::unique_ptr<Process> process = std::make_unique<Process>(program, args);
    process->start();
    std::string a = "ls -la\n";
    process->send(a);
    usleep(4000);
    std::string b = process->get(1000);
    std::cout << "Contents: " << b << '\n';
    std::string c = "cat test.txt\n";
    process->send(c);
    usleep(4000);
    std::string d = process->get(1000);
    std::cout << "Contents: " << d << '\n';
    return 0;
}
