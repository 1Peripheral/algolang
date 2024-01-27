#include "../include/ast.h"

AST::AST() {}

void AST::addStmnt(Stmnt& stmnt) {
   this->stmnts.push_back(stmnt);
}

void Stmnt::print() {}

VarStmnt::VarStmnt() {
   this->type = VARSTMNT;
}

void VarStmnt::print() {
   std::cout << "[VarStmnt]" << std::endl;
}

VarStmnt::VarStmnt(Token ident, Expr value) {
   this->type = VARSTMNT;
   this->ident = ident;
   this->value = value;
}

PrimaryExpr::PrimaryExpr() {
   this->type = PRIMARYEXPR;
}

PrimaryExpr::PrimaryExpr(Token value) {
   this->type = PRIMARYEXPR;
   this->value = value;
}

void PrimaryExpr::print() {
   std::cout << "[PrimaryExpr]" << std::endl;
}

UnaryExpr::UnaryExpr() {
   this->type = UNARYEXPR;
}

void UnaryExpr::print() {
   std::cout << "[UnaryExpr]" << std::endl;
}

BinaryExpr::BinaryExpr() {
   this->type = BINARYEXPR;
}

BinaryExpr::BinaryExpr(Expr left, Expr right, Token oper) {
   this->type = BINARYEXPR;
   this->left = left;
   this->right = right;
   this->oper = oper;
}

void BinaryExpr::print() {
   std::cout << "[BinaryExpr]" << std::endl;
}
