#pragma once

#include "ast.h"
#include "lexer.h"

class Parser
{
public:
  Parser(Lexer lexer);
  AST parse();

private:
  Stmnt *statement();
  Expr *comparison();
  Expr *expression();
  BinaryExpr *term();
  UnaryExpr *unary();
  Expr *primary();
  void newLine();

  void nextToken();
  void match(TokenKind kind);
  void match();
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
