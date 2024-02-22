#include "../include/ast.h"

AST::AST()
{
}

void AST::addStmnt(Stmnt *stmnt)
{
  this->stmnts.push_back(stmnt);
}

UnaryExpr::UnaryExpr()
{
  this->type = UNARYEXPR;
}

BinaryExpr::BinaryExpr()
{
  this->type = BINARYEXPR;
  this->left = nullptr;
  this->right = nullptr;
  this->oper = Token(NONE, "");
}

WriteStmnt::WriteStmnt()
{
  this->type = WRITESTMNT;
  this->expr = nullptr;
  this->stringLiteral = std::string();
}

ReadStmnt::ReadStmnt()
{
  this->type = READSTMNT;
  this->variableType = NONE;
}

ReadStmnt::ReadStmnt(Token variable, TokenKind variableType)
{
  this->type = READSTMNT;
  this->variable = variable;
  this->variableType = variableType;
}

VarStmnt::VarStmnt()
{
  this->type = VARSTMNT;
}

IfStmnt::IfStmnt()
{
  this->type = IFSTMNT;
  this->expr = nullptr;
}

PrimaryExpr::PrimaryExpr()
{
  this->type = PRIMARYEXPR;
  this->expr = nullptr;
}

FuncCall::FuncCall()
{
  this->type = FUNCCALL;
}

WhileStmnt::WhileStmnt()
{
  this->type = WHILESTMNT;
  this->expr = nullptr;
}

ContinueStmnt::ContinueStmnt()
{
  this->type = CONTINUESTMNT;
}

BreakStmnt::BreakStmnt()
{
  this->type = BREAKSTMNT;
}

ArrayExpr::ArrayExpr()
{
  this->type = ARRAYEXPR;
}

FunctionDecl::FunctionDecl()
{
  this->type = FUNCDECL;
}
