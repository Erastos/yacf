#include "process.h"
#include <iostream>


int main (int argc, char* argv[]) {
    std::vector<std::string> args;
    args.push_back("10");
    std::string program = "/bin/sleep";
    Process process(program, args);
    process.start();
    return 0;
}
