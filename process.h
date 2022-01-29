#ifndef PROCESS_HEADER
#define PROCESS_HEADER

#include <string>
#include <vector>

#include <stdlib.h>
#include <unistd.h>

class Process {
public:
  Process(std::string name, std::vector<std::string[]> args);
  void construct();
private:
  int _PID;
  std::string _name;
  std::vector<std::string> _args;
};

#endif
