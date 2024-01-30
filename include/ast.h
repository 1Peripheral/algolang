#pragma once

#include <iostream>

#include <vector>
#include "token.h"

enum NodeType {
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
};

class Stmnt {
public:
   virtual void print();

   NodeType type;
};

class Expr {
public:
   virtual ~Expr();
   virtual void print();

   NodeType type;
};

class AST {
public:
   AST();
   void addStmnt(Stmnt* stmnt);

   std::vector<Stmnt*> stmnts;
};

// EXPRESSIONS
class PrimaryExpr : public Expr {
public:
   PrimaryExpr();
   ~PrimaryExpr();
   PrimaryExpr(Token value);
   void print() override;

   Token value;
   // OR
   Expr* expr;
};

class BinaryExpr : public Expr {
public:
   BinaryExpr();
   ~BinaryExpr();
   BinaryExpr(Expr* left, Expr* right, Token oper);
   void print() override;

   Expr* left;
   Expr* right;
   Token oper;
};

class UnaryExpr : public Expr {
public:
   UnaryExpr();
   ~UnaryExpr();
   UnaryExpr(PrimaryExpr right, Token oper);
   void print() override;

   Token oper;
   PrimaryExpr right;
};

class NoneExpr : public Expr {
   ~NoneExpr();
   void print();
};

// STATEMENTS
class WriteStmnt : public Stmnt{
public:
   WriteStmnt();
   ~WriteStmnt();
   WriteStmnt(Expr* expr);
   void print();

   Expr* expr;
   std::string stringLiteral;
};


class ReadStmnt: public Stmnt {
public:
   ReadStmnt();
   ~ReadStmnt();
   ReadStmnt(Token variable);
   void print() override;

   Token variable;
};

class VarStmnt : public Stmnt {
public:
   VarStmnt();
   VarStmnt(Token ident, Expr* value);
   void print() override;

   Token ident;
   Expr* value;
};

class IfStmnt : public Stmnt {
public:
   IfStmnt();
   ~IfStmnt();
   void print() override;

   Expr* expr;
   std::vector<Stmnt*> stmnts;
};

class WhileStmnt : public Stmnt {
public:
   WhileStmnt();
   ~WhileStmnt();
   void print() override;

   Expr* expr;
   std::vector<Stmnt*> stmnts;
};

class ContinueStmnt : public Stmnt {
public:
   ContinueStmnt();
   ~ContinueStmnt();
};

class BreakStmnt : public Stmnt {
public:
   BreakStmnt(); 
   ~BreakStmnt();
};
