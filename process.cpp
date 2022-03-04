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
    this->_write_pipe = -1;
    this->_read_pipe = -1;
    createArgsString();
    instantiatePipes();
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

void Process::instantiatePipes() {
    int pipes[2];
    int ret = pipe(pipes);
    if (ret == -1) {
        char error[40];
        sprintf(error, "Pipes for %s failed to be created: ", this->_name.c_str());
        perror(error);
    }
    this->_write_pipe = pipes[1];
    this->_read_pipe = pipes[0];
}

int Process::getPID() {
    return this->_PID;
}


void Process::start() {
    int pid;
    // Create an array to store the arguments
    // Execute the provided process application
    if ((pid = fork()) == 0) {
        int re1,re2;
        re1 = dup2(this->_read_pipe, STDIN_FILENO);
        re2 = dup2(this->_write_pipe, STDOUT_FILENO);
        close(this->_read_pipe);
        close(this->_write_pipe);
        if (re1 == -1 || re2 == -1) {
            perror("Could not change file descriptor");
        }

        int ret = execv(this->_name.c_str(), this->_args_string);
        if (ret != 0) {
            char error[40];
            sprintf(error, "Error in Starting Process PID %d: ", pid);
            perror(error);
        }
    } else {
        this->_PID = pid;
    }

}

Process::~Process() {
    delete[] this->_args_string;
}
