#include "../include/ast.h"

AST::AST() {}

void AST::addStmnt(Stmnt *stmnt) { this->stmnts.push_back(stmnt); }

void Stmnt::print() {}

Expr::~Expr() {}

void Expr::print() {}

PrimaryExpr::~PrimaryExpr() {}

PrimaryExpr::PrimaryExpr(Token value) {
  this->type = PRIMARYEXPR;
  this->value = value;
}

void PrimaryExpr::print() {
  std::cout << "[PrimaryExpr]" << std::endl;
  std::cout << this->value.toString() << std::endl;
}

UnaryExpr::UnaryExpr() { this->type = UNARYEXPR; }

UnaryExpr::~UnaryExpr() {}

void UnaryExpr::print() {
  std::cout << "[UnaryExpr]" << std::endl;
  std::cout << this->oper.toString() << std::endl;
  this->right.print();
}

BinaryExpr::BinaryExpr() {
  this->type = BINARYEXPR;
  this->left = nullptr;
  this->right = nullptr;
  this->oper = Token(NONE, "");
}

BinaryExpr::~BinaryExpr() {}

BinaryExpr::BinaryExpr(Expr *left, Expr *right, Token oper) {
  this->type = BINARYEXPR;
  this->left = left;
  this->right = right;
  this->oper = oper;
}

void BinaryExpr::print() {
  std::cout << "[BinaryExpr]" << std::endl;
  if (this->left)
    this->left->print();
  std::cout << this->oper.toString() << std::endl;
  if (this->right)
    this->right->print();
}

NoneExpr::~NoneExpr() {}

void NoneExpr::print() {}

WriteStmnt::WriteStmnt() {
  this->type = WRITESTMNT;
  this->expr = nullptr;
  this->stringLiteral = std::string();
}

WriteStmnt::WriteStmnt(Expr *expr) {
  this->type = WRITESTMNT;
  this->stringLiteral = std::string();
  this->expr = expr;
}

WriteStmnt::~WriteStmnt() {}

void WriteStmnt::print() {}

ReadStmnt::ReadStmnt() { this->type = READSTMNT; }

ReadStmnt::~ReadStmnt() {}

ReadStmnt::ReadStmnt(Token variable) {
  this->type = READSTMNT;
  this->variable = variable;
}

void ReadStmnt::print() {}

VarStmnt::VarStmnt() { this->type = VARSTMNT; }

void VarStmnt::print() {
  std::cout << "[VarStmnt]" << std::endl;
  std::cout << this->ident.toString() << std::endl;
  this->value->print();
}

VarStmnt::VarStmnt(Token ident, Expr *value) {
  this->type = VARSTMNT;
  this->ident = ident;
  this->value = value;
}

IfStmnt::IfStmnt() {
  this->type = IFSTMNT;
  this->expr = nullptr;
}

IfStmnt::~IfStmnt() {}

void IfStmnt::print() {}

PrimaryExpr::PrimaryExpr() {
  this->type = PRIMARYEXPR;
  this->expr = nullptr;
}

WhileStmnt::WhileStmnt() {
  this->type = WHILESTMNT;
  this->expr = nullptr;
}
WhileStmnt::~WhileStmnt() {}

void WhileStmnt::print() {}

ContinueStmnt::ContinueStmnt() { this->type = CONTINUESTMNT; }
ContinueStmnt::~ContinueStmnt() {}

BreakStmnt::BreakStmnt() { this->type = BREAKSTMNT; }
BreakStmnt::~BreakStmnt() {}
