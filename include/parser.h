#pragma once

#include "lexer.h"
#include "ast.h"

class Parser {
public:
   Parser(Lexer lexer);
   /* void program(); */
   AST program();

private:
   void statement();
   void comparison();
   /* void expression(); */
   Expr expression();
   /* void term(); */
   BinaryExpr term();
   /* void unary(); */
   UnaryExpr unary();
   /* void primary(); */
   PrimaryExpr primary();
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
   AST ast;

private:
   Logger _logger;
};
