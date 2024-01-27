#include "../include/ast.h"

AST::AST() {}

void AST::addStmnt(Stmnt* stmnt) {
   this->stmnts.push_back(stmnt);
}

void Stmnt::print() {}

Expr::~Expr() {}

void Expr::print() {}

VarStmnt::VarStmnt() {
   this->type = VARSTMNT;
}

void VarStmnt::print() {
   std::cout << "[VarStmnt]" << std::endl;
   std::cout << this->ident.toString() << std::endl;
   this->value->print();
}

VarStmnt::VarStmnt(Token ident, Expr* value) {
   this->type = VARSTMNT;
   this->ident = ident;
   this->value = value;
}

PrimaryExpr::PrimaryExpr() {
   this->type = PRIMARYEXPR;
}

PrimaryExpr::~PrimaryExpr() {}

PrimaryExpr::PrimaryExpr(Token value) {
   this->type = PRIMARYEXPR;
   this->value = value;
}

void PrimaryExpr::print() {
   std::cout << "[PrimaryExpr]" << std::endl;
   std::cout << this->value.toString() << std::endl;
}

UnaryExpr::UnaryExpr() {
   this->type = UNARYEXPR;
}

UnaryExpr::~UnaryExpr() {}

void UnaryExpr::print() {
   std::cout << "[UnaryExpr]" << std::endl;
   std::cout << this->oper.toString() << std::endl;
   this->right.print();
}

BinaryExpr::BinaryExpr() {
   this->type = BINARYEXPR;
}

BinaryExpr::~BinaryExpr() {}

BinaryExpr::BinaryExpr(Expr* left, Expr* right, Token oper) {
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
