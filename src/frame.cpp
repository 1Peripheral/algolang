#include "../include/frame.h"

Frame::Frame() {}

void Frame::add(std::string name, RuntimeVal val) {
  this->vars[name] = val;
}

RuntimeVal Frame::get(std::string name) {
  return this->vars[name];
}

bool Frame::exists(std::string name) {
  if (this->vars.find(name) == this->vars.end())
    return false;

  return true;
}

StackFrame::StackFrame() {}

void StackFrame::make() {
  this->frames.push_back(Frame());
}

void StackFrame::add(std::string name, RuntimeVal val) {
  this->frames.begin()->add(name, val);
}

bool StackFrame::exists(std::string name) {
  return this->frames.begin()->exists(name);
}

RuntimeVal StackFrame::get(std::string name) {
  return this->frames.begin()->get(name);
}

void StackFrame::drop() {
  this->frames.pop_front();
}
