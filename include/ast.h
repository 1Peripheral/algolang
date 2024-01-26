#pragma once

#include <vector>
#include "token.h"

enum NodeType {
   STMNT,
   IFSTMNT,
   VARSTMNT,
   EXPR,
   PROGRAM,
   WRITEEXPR,
   READEXPR,
   BINARYEXPR,
   UNARYEXPR,
   PRIMARYEXPR,
};

class Stmnt {
public:
   NodeType type;
};

class Expr {
public:
   NodeType type;
};

class Program {
public:
   Program();
   void addStmnt(Stmnt stmnt);

   std::vector<Stmnt> stmnts;
};

class PrimaryExpr : Expr {
public:
   PrimaryExpr(Token value);

   Token value;
};

class BinaryExpr : Expr {
public:
   BinaryExpr(Expr left, Expr right, Token oper);

   Expr left;
   Expr right;
   Token oper;
};

class UnaryExpr : Expr {
public:
   UnaryExpr(PrimaryExpr right, Token oper);

   Token oper;
   PrimaryExpr right;
};

class WriteStmnt : Stmnt {
public:
   WriteStmnt(Token operand);

   Token operand;
};

class ReadStmnt: Stmnt {
public:
   ReadStmnt(Token operand);

   Token operand;
};

class VarStmnt : Stmnt {
public:
   VarStmnt(Token ident, Expr value);

   Token ident;
   Expr value;
};

class IfStmnt : Stmnt {
public:
   IfStmnt(Expr comparison);

   Expr comparison;
};
