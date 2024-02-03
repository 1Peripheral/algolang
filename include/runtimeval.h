#pragma once

#include "logger.h"
#include "token.h"
#include "utils.h"

class RuntimeVal {
public:
  RuntimeVal();

  RuntimeVal operator+(const RuntimeVal &other);
  RuntimeVal operator-(const RuntimeVal &other);
  RuntimeVal operator/(const RuntimeVal &other);
  RuntimeVal operator*(const RuntimeVal &other);

  void operator=(const RuntimeVal &other);

  bool operator>(const RuntimeVal &other);
  bool operator>=(const RuntimeVal &other);
  bool operator<(const RuntimeVal &other);
  bool operator<=(const RuntimeVal &other);
  bool operator==(const RuntimeVal &other);
  bool operator!=(const RuntimeVal &other);

  TokenKind getType();
  void setAsNumber(double num);
  void setAsString(std::string str);
  void print() const;

  std::string str;
  double number;
  TokenKind type;

private:
  bool matchType(const RuntimeVal &other, TokenKind type1, TokenKind type2);

  Logger _logger;
};
