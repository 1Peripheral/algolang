#pragma once

#include <deque>
#include <unordered_map>
#include "runtimeval.h"

class Frame {
public:
  Frame();
  void add(std::string name, RuntimeVal val);
  RuntimeVal get(std::string name);
  bool exists(std::string name);

private:
  std::unordered_map<std::string, RuntimeVal> vars;
};

class StackFrame {
public :
  StackFrame();

  void make();
  void add(std::string name, RuntimeVal val);
  bool exists(std::string name);
  RuntimeVal get(std::string name);
  void drop();

private:
  std::deque<Frame> frames;
};
