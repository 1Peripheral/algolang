#pragma once

#include <iostream>
#include <vector>

#include "token.h"

enum NodeType
{
  STMNT = 0,
  IFSTMNT,
  READSTMNT,
  WRITESTMNT,
  VARSTMNT,
  WHILESTMNT,
  CONTINUESTMNT,
  BREAKSTMNT,
  EXPR,
  NONEEXPR,
  BINARYEXPR,
  TERMEXPR,
  UNARYEXPR,
  PRIMARYEXPR,
  ARRAYEXPR,
  FUNCDECL,
  FUNCCALL,
};

class Stmnt
{
public:
  NodeType type;
};

class Expr
{
public:
  NodeType type;
};

class AST
{
public:
  AST();
  void addStmnt(Stmnt *stmnt);

  std::vector<Stmnt *> stmnts;
};

// EXPRESSIONS
class PrimaryExpr : public Expr
{
public:
  PrimaryExpr();

  Token value;
  // OR
  Expr *expr;
};

class BinaryExpr : public Expr
{
public:
  BinaryExpr();

  Expr *left;
  Expr *right;
  Token oper;
};

class UnaryExpr : public Expr
{
public:
  UnaryExpr();

  Token oper;
  PrimaryExpr right;
};

class NoneExpr : public Expr
{
};

// STATEMENTS
class WriteStmnt : public Stmnt
{
public:
  WriteStmnt();

  Expr *expr;
  std::string stringLiteral;
};

class ReadStmnt : public Stmnt
{
public:
  ReadStmnt();
  ReadStmnt(Token variable, TokenKind variableType);

  Token variable;
  TokenKind variableType;
};

class VarStmnt : public Stmnt
{
public:
  VarStmnt();

  Token ident;
  Expr *value;
};

class IfStmnt : public Stmnt
{
public:
  IfStmnt();

  Expr *expr;
  std::vector<Stmnt *> stmnts;
};

class WhileStmnt : public Stmnt
{
public:
  WhileStmnt();

  Expr *expr;
  std::vector<Stmnt *> stmnts;
};

class ContinueStmnt : public Stmnt
{
public:
  ContinueStmnt();
};

class BreakStmnt : public Stmnt
{
public:
  BreakStmnt();
};

class ArrayExpr : public Expr
{
public:
  ArrayExpr();

  std::vector<Expr *> elmnts;
};
