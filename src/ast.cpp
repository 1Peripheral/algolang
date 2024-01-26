#include "../include/ast.h"

Program::Program() {}

void Program::addStmnt(Stmnt stmnt) {
   this->stmnts.push_back(stmnt);
}

PrimaryExpr::PrimaryExpr(Token value) {
   this->type = PRIMARYEXPR;
   this->value = value;
}

VarStmnt::VarStmnt(Token ident, Expr value) {
   this->type = VARSTMNT;
   this->ident = ident;
   this->value = value;
}
