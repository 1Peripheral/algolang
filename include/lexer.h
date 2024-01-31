#pragma once

#include "logger.h"
#include "token.h"
#include <iostream>

class Lexer {
public:
  Lexer(std::string source);

  void nextChar();
  char peek();
  Token nextToken();
  void skipWhiteSpace();
  void skipComment();

public:
  char curChar;
  int curIndex;

private:
  Logger _logger;
  std::string source;
};
