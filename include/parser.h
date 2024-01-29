#pragma once

#include "lexer.h"
#include "ast.h"

class Parser {
public:
   Parser(Lexer lexer);
   AST program();

private:
   Stmnt* statement();
   Expr* comparison();
   Expr* expression();
   BinaryExpr* term();
   UnaryExpr* unary();
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
