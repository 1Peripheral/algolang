#pragma once

#include <iostream>
#include <unordered_map>
#include "logger.h"
#include "token.h"

enum class Alphabet {
   OPEN_BRACE,
   CLOSE_BRACE,
   OPEN_CURLY_BRACE,
   CLOSE_CURLY_BRACE,
   COMMA,
   QUOTE,
   MINUS,
   PLUS,
   ASTERISK,
   SLASH,
   GT,
   LT,
   EQUAL,
   EXCLAMATION,
   ENDLINE,
   NULLCHAR,
   NUMBER,
   ALPHA,
};

class Lexer {
public :


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

   static std::unordered_map<char, Alphabet> alphabetDict; //For lookup
   static void initDict(); 
};
   