#include "process.h"
#include <iostream>


int main (int argc, char* argv[]) {
    std::vector<std::string> args;
    args.push_back("test");
    std::string program = "/bin/echo";
    Process process(program, args);
    return 0;
}
