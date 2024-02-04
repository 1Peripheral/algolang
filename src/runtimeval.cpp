#include "../include/runtimeval.h"

RuntimeVal::RuntimeVal()
{
  this->str = "";
  this->number = 0;
  type = NUMBER;
}

void RuntimeVal::operator=(const RuntimeVal &other)
{
  if (other.type == NUMBER)
  {
    this->number = other.number;
    this->type = other.type;
  }
  else if (other.type == STRING)
  {
    this->str = other.str;
    this->type = other.type;
  }
  else
    _logger.panic("Unsupported operation");
}

RuntimeVal RuntimeVal::operator+(const RuntimeVal &other)
{
  RuntimeVal result;
  if (this->matchType(other, NUMBER, NUMBER))
    result.number = this->number + other.number;
  else if (this->matchType(other, NUMBER, STRING))
  {
    result.str = numToString(this->number) + other.str;
    result.type = STRING;
  }
  else if (this->matchType(other, STRING, NUMBER))
  {
    result.str = this->str + numToString(other.number);
    result.type = STRING;
  }
  else if (this->matchType(other, STRING, STRING))
  {
    result.str = this->str + other.str;
    result.type = STRING;
  }
  else
    _logger.panic("Unsupported operation");
  return result;
}

RuntimeVal RuntimeVal::operator-(const RuntimeVal &other)
{
  RuntimeVal result;
  if (!this->matchType(other, NUMBER, NUMBER))
    _logger.panic("Unsupported operation");
  result.type = NUMBER;
  result.number = this->number - other.number;
  return result;
}

RuntimeVal RuntimeVal::operator/(const RuntimeVal &other)
{
  RuntimeVal result;
  if (!this->matchType(other, NUMBER, NUMBER))
    _logger.panic("Unsupported operation");
  result.type = NUMBER;
  result.number = this->number / other.number;
  return result;
}

RuntimeVal RuntimeVal::operator*(const RuntimeVal &other)
{
  RuntimeVal result;
  if (!this->matchType(other, NUMBER, NUMBER))
    _logger.panic("Unsupported operation");
  result.type = NUMBER;
  result.number = this->number * other.number;
  return result;
}

bool RuntimeVal::operator>(const RuntimeVal &other)
{
  if (this->matchType(other, NUMBER, NUMBER))
    return this->number > other.number;
  else if (this->matchType(other, STRING, STRING))
    return this->str > other.str;
  return false;
}

bool RuntimeVal::operator>=(const RuntimeVal &other)
{
  if (this->matchType(other, NUMBER, NUMBER))
    return this->number >= other.number;
  else if (this->matchType(other, STRING, STRING))
    return this->str >= other.str;
  return false;
}

bool RuntimeVal::operator<(const RuntimeVal &other)
{
  if (this->matchType(other, NUMBER, NUMBER))
    return this->number < other.number;
  else if (this->matchType(other, STRING, STRING))
    return this->str < other.str;
  return false;
}

bool RuntimeVal::operator<=(const RuntimeVal &other)
{
  if (this->matchType(other, NUMBER, NUMBER))
    return this->number <= other.number;
  else if (this->matchType(other, STRING, STRING))
    return this->str <= other.str;
  return false;
}

bool RuntimeVal::operator==(const RuntimeVal &other)
{
  if (this->matchType(other, NUMBER, NUMBER))
    return this->number == other.number;
  else if (this->matchType(other, STRING, STRING))
    return this->str == other.str;
  return false;
}

bool RuntimeVal::operator!=(const RuntimeVal &other)
{
  if (this->matchType(other, NUMBER, NUMBER))
    return this->number != other.number;
  else if (this->matchType(other, STRING, STRING))
    return this->str != other.str;
  return false;
}

bool RuntimeVal::matchType(const RuntimeVal &other, TokenKind type1, TokenKind type2)
{
  return this->type == type1 && other.type == type2;
}
TokenKind RuntimeVal::getType()
{
  return this->type;
}

void RuntimeVal::setAsNumber(double num)
{
  this->number = num;
  this->type = NUMBER;
}
void RuntimeVal::setAsString(std::string str)
{
  this->str = str;
  this->type = STRING;
}

void RuntimeVal::print() const
{
  if (this->type == NUMBER)
    std::cout << this->number << "\n";
  else
    std::cout << this->str << "\n";
}
