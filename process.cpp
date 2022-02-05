#include <string>
#include <algorithm>

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

#include "process.h"


Process::Process(std::string name, std::vector<std::string> args) {
    this->_name = name;
    this->_PID = 0;
    this->_args = args;
    construct();
}

void Process::construct() {
    int pid;
    const char* array[_args.size()+2];
    array[0] = _name.c_str();
    // First argument is the name of the application
    // Iterate through to add the arguments to the array
    for (int i = 0; i < this->_args.size(); i++) {
        array[i+1] = this->_args[i].c_str();
    }
    array[_args.size()+1] = NULL;
    
    // Add the required NULL to the end of the array
    // Create an array to store the arguments
    // Execute the provdied process application
    if ((pid = fork()) != 0) {
        int ret = execv(this->_name.c_str(), (char**)array);
        if (ret != 0) {
            perror("Error: ");
        }
        // Pause the process
        kill(pid, SIGSTOP);
    } else {
        this->_PID = pid;
    }
}
