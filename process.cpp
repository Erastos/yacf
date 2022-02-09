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
    this->_args_string = new char*[this->_args.size()+2];
    createArgsString();
}

void Process::createArgsString() {
    // First argument is the name of the application
    this->_args_string[0] = (char* const) _name.c_str();

    // Iterate through to add the arguments to the array
    for (int i = 0; i < this->_args.size(); i++) {
        _args_string[i+1] = (char* const) this->_args[i].c_str();
    }

    // Add the required NULL to the end of the array
    _args_string[_args.size()+1] = NULL;
}

void Process::start() {
    int pid;
    // Create an array to store the arguments
    // Execute the provided process application
    if ((pid = fork()) != 0) {
        int ret = execv(this->_name.c_str(), this->_args_string);
        if (ret != 0) {
            char error[40];
            sprintf(error, "Error in Starting Process PID %d: ", pid);
            perror("Error starting process: ");
        }
    } else {
        this->_PID = pid;
    }

}

Process::~Process() {
    delete[] this->_args_string;
}
