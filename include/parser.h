#pragma once

#include "lexer.h"

class Parser {
public:
   Parser(Lexer lexer);

private:
   void program();
   void statement();
   void comparison();
   void expression();
   void term();
   void unary();
   void primary();
   void newLine();

   void nextToken();
   void match(TokenKind kind);
   bool checkToken(TokenKind kind);
   bool checkPeek(TokenKind kind);

public:
   Lexer lexer;
   Token curToken;
   Token peekToken;

private:
   Logger _logger;
};
