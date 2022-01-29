#include <string>
#include <algorithm>

#include <stdlib.h>
#include <unistd.h>

#include "process.h"


Process::Process(std::string name, std::vector<std::string> args) {
    this->_name = name;
    this->_PID = 0;
    this->_args = args;
}

void Process::construct() {
    int pid;
    
    if ((pid = fork()) == 0) {
        execv(this->_name, this->_args);
    }
}