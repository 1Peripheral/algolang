#pragma once

#include <iostream>
#include <vector>
#include "token.h"

enum NodeType {
   STMNT,
   IFSTMNT,
   VARSTMNT,
   EXPR,
   WRITEEXPR,
   READEXPR,
   BINARYEXPR,
   UNARYEXPR,
   PRIMARYEXPR,
};

class Stmnt {
public:
   virtual void print();

   NodeType type;
};

class Expr {
public:
   void print();

   NodeType type;
};

class AST {
public:
   AST();
   void addStmnt(Stmnt& stmnt);

   std::vector<Stmnt> stmnts;
};

class PrimaryExpr : Expr {
public:
   PrimaryExpr();
   PrimaryExpr(Token value);
   void print();

   Token value;
};

class BinaryExpr : public Expr {
public:
   BinaryExpr();
   BinaryExpr(Expr left, Expr right, Token oper);
   void print();

   Expr left;
   Expr right;
   Token oper;
};

class UnaryExpr : public Expr {
public:
   UnaryExpr();
   UnaryExpr(PrimaryExpr right, Token oper);
   void print();

   Token oper;
   PrimaryExpr right;
};

class WriteStmnt : public Stmnt {
public:
   WriteStmnt(Token operand);
   void print() override;

   Token operand;
};

class ReadStmnt: public Stmnt {
public:
   ReadStmnt(Token operand);
   void print() override;

   Token operand;
};

class VarStmnt : public Stmnt {
public:
   VarStmnt();
   VarStmnt(Token ident, Expr value);
   void print() override;

   Token ident;
   Expr value;
};

class IfStmnt : public Stmnt {
public:
   IfStmnt(Expr comparison);
   void print() override;

   Expr comparison;
};
