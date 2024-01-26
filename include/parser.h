#pragma once

#include "lexer.h"

class Parser {
public:
   Parser(Lexer lexer);
   void program();

private:
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

   bool isComparisonOperator();

public:
   Lexer lexer;
   Token curToken;
   Token peekToken;

private:
   Logger _logger;
};
