#pragma once

#include <string>

inline std::string numToString(double number);

std::string numToString(double number)
{
  std::string result = std::to_string(number);
  for (int i = result.length() - 1; i >= 0; i--)
  {
    if (result[i] == '0')
      result.erase(i);
    else if (result[i] == '.')
    {
      result.erase(i);
      break;
    }
  }
  return result;
}
