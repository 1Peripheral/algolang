#pragma once

#include <iostream>

#include "logger.h"
#include "token.h"

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
