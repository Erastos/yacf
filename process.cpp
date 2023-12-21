#include <cerrno>
#include <string>
#include <algorithm>
#include <iostream>

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/file.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "process.h"

namespace py = pybind11;

Process::Process(std::string name, std::vector<std::string> args) {
    this->_name = name;
    this->_PID = 0;
    this->_args = args;
    this->_args_string = new char*[this->_args.size()+2];
    this->_write_pipe_stdin = -1;
    this->_read_pipe_stdin = -1;
    this->_write_pipe_stdin = -1;
    this->_read_pipe_stdin = -1;
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
    int pipesStdout[2];
    int pipesStdin[2];
    int ret1 = pipe(pipesStdout);
    int ret2 = pipe(pipesStdin);
    if (ret1 == -1 || ret2 == -1) {
        char error[40];
        sprintf(error, "Pipes for %s failed to be created: ", this->_name.c_str());
        perror(error);
    }
    this->_write_pipe_stdout = pipesStdout[1];
    this->_read_pipe_stdout = pipesStdout[0];
    this->_write_pipe_stdin = pipesStdin[1];
    this->_read_pipe_stdin = pipesStdin[0];
}

int Process::getPID() {
    return this->_PID;
}

void Process::testPrint() {
    char buf[100];
    read(this->_read_pipe_stdout, buf, 99);
    buf[99] = '\0';
    printf("Buffer Contents: %s", buf);
}


void Process::start() {
    int pid;
    // Create an array to store the arguments
    // Execute the provided process application
    if ((pid = fork()) == 0) {
        int re1,re2,re3,re4;

        // Close unneeded pipes
        close(this->_read_pipe_stdout);
        close(this->_write_pipe_stdin);

        // Set pipe fds to stdin and stdout
        re1 = dup2(this->_read_pipe_stdin, STDIN_FILENO);
        re2 = dup2(this->_write_pipe_stdout, STDOUT_FILENO);

        close(this->_read_pipe_stdin);
        close(this->_write_pipe_stdout);

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
        // Close unneeded pipes
        close(this->_write_pipe_stdout);
        close(this->_read_pipe_stdin);

        this->_PID = pid;

        // testPrint();
    }

}

 std::string Process::get(int bufferSize) {
     std::string buffer;
     char cBuff[bufferSize];
     memset(cBuff, 0, bufferSize);

     // int ret = flock(this->_write_pipe, LOCK_EX);
     // if (ret == -1) {
     //     perror("Unable to Create File Lock on Read End of Main Process");
     // }
     read(this->_read_pipe_stdout, cBuff, bufferSize-1);
     // ret = flock(this->_write_pipe, LOCK_UN);
     // if (ret == -1) {
     //     perror("Unable to Remove File Lock on Read End of Main Process");
     // }

     cBuff[bufferSize-1] = '\0';
     return std::string(cBuff);
 }

  void Process::send(std::string content) {
      // errno = 0;
      // int ret = flock(this->_write_pipe, LOCK_EX);
      // if (ret == -1) {
      //     perror("Unable to Create File Lock on Write End of Main Process");
      // }
      const char* buffer = content.data();
      write(this->_write_pipe_stdin, buffer, content.size());
      // ret = flock(this->_write_pipe, LOCK_UN);
      // if (ret == -1) {
      //     perror("Unable to Remove File Lock on Write End of Main Process");
      // }
  }

Process::~Process() {
    delete[] this->_args_string;
    close(this->_read_pipe_stdin);
    close(this->_read_pipe_stdout);
    close(this->_write_pipe_stdin);
    close(this->_write_pipe_stdout);
    kill(this->_PID, SIGTERM);
}

