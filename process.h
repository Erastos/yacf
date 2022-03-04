#ifndef PROCESS_HEADER
#define PROCESS_HEADER

#include <string>
#include <vector>

#include <stdlib.h>
#include <unistd.h>

class Process {
public:
  Process(std::string name, std::vector<std::string> args);
  void createArgsString();
  void start();
  void instantiatePipes();
  int getPID();
  std::string get(int bufSize);
  void send(std::string content);
  ~Process();

private:
  int _PID;
  std::string _name;
  std::vector<std::string> _args;
  char **_args_string;
  int _write_pipe;
  int _read_pipe;
};

#endif
