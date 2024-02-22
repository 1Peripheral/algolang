#include "../include/interpreter.h"

Interpreter::Interpreter()
{
  this->breakLoopFlag = false;
  this->continueLoopFlag = false;
}

Interpreter::Interpreter(AST program)
{
  this->program = program;
  this->breakLoopFlag = false;
  this->continueLoopFlag = false;
}
void Interpreter::run(AST program)
{
  this->program = program;
  this->traverse();
}

void Interpreter::traverse()
{
  this->traverse(program.stmnts);
}

void Interpreter::traverse(std::vector<Stmnt *> stmnts)
{
  for (auto stmnt = stmnts.begin(); stmnt < stmnts.end(); stmnt++)
  {
    switch ((*stmnt)->type)
    {
    case VARSTMNT: {
      VarStmnt *varStmnt = (VarStmnt *)*stmnt;
      this->variables[varStmnt->ident.lexeme] = this->evaluate(varStmnt->value);
      break;
    }
    case FUNCDECL: {
      FunctionDecl *funcDecl = (FunctionDecl *)*stmnt;
      functions[funcDecl->identifier] = *funcDecl;
      break;
    }
    case WRITESTMNT: {
      WriteStmnt *writeStmnt = (WriteStmnt *)*stmnt;
      this->evaluate(writeStmnt->expr).print();
      std::cout << '\n';
      break;
    }
    case READSTMNT: {
      ReadStmnt *readStmnt = (ReadStmnt *)*stmnt;
      RuntimeVal input;
      if (readStmnt->variableType == NUMBER)
      {
        std::cin >> input.number;
        input.type = NUMBER;
      }
      else
      {
        std::cin >> input.str;
        input.type = STRING;
      }
      this->variables[readStmnt->variable.lexeme] = input;
      break;
    }
    case IFSTMNT: {
      IfStmnt *ifStmnt = (IfStmnt *)*stmnt;
      RuntimeVal comparisonResult = this->evaluateComparison(ifStmnt->expr);
      if (comparisonResult.number)
      {
        this->traverse(ifStmnt->stmnts);
      }
      break;
    }
    case WHILESTMNT: {
      WhileStmnt *whileStmnt = (WhileStmnt *)*stmnt;
      RuntimeVal comparisonResult = this->evaluateComparison(whileStmnt->expr);
      if (!comparisonResult.number)
        break;
      this->traverse(whileStmnt->stmnts);
      if (breakLoopFlag)
      {
        breakLoopFlag = false;
        break;
      }
      // decrementing the iterator in order to re evaluate the while comparison.
      stmnt--;
      break;
    }
    case FUNCCALL: {
      FuncCall *funcCall = (FuncCall *)*stmnt;
      FunctionDecl function = this->functions.find(funcCall->identifier)->second;
      this->traverse(function.stmnts);
      break;
    }
    case CONTINUESTMNT: {
      _logger.warning("Not yet implemented (continue)");
      continueLoopFlag = true;
      return;
    }
    case BREAKSTMNT: {
      _logger.warning("Not yet implemented (break)");
      breakLoopFlag = true;
      return;
    }
    default:
      _logger.panic("Unknown statement");
    }
  }
}

RuntimeVal Interpreter::evaluate(Expr *expr)
{
  RuntimeVal result;
  switch (expr->type)
  {
  case BINARYEXPR:
    result = this->evaluateBinary(expr);
    break;
  case ARRAYEXPR: {
    ArrayExpr *arrayExpr = (ArrayExpr *)expr;
    for (auto value : arrayExpr->elmnts)
    {
      result.type = ARRAY;
      result.addToArray(this->evaluate(value));
    }
    break;
  }
  case FUNCCALL: {
    FuncCall *funCall = (FuncCall *)expr;
    auto func = this->functions.find(funCall->identifier);
    if (func != this->functions.end())
    {
      this->traverse(func->second.stmnts);
    }
    else
    {
      _logger.panic("Call to an undeclared function : " + funCall->identifier + " .");
    }
    break;
  }
  default:
    result.number = 0;
  }

  return result;
}

RuntimeVal Interpreter::evaluateComparison(Expr *expr)
{
  BinaryExpr *bexpr = (BinaryExpr *)expr;
  RuntimeVal result = {};

  RuntimeVal left = this->evaluateBinary(bexpr->left);
  RuntimeVal right = {};
  if (bexpr->right)
    right = this->evaluateComparison(bexpr->right);

  switch (bexpr->oper.kind)
  {
  case TokenKind::EQEQ: {
    result.number = left == right;
    break;
  }
  case TokenKind::GT: {
    result.number = left > right;
    break;
  }
  case TokenKind::GTEQ: {
    result.number = left >= right;
    break;
  }
  case TokenKind::LT: {
    result.number = left < right;
    break;
  }
  case TokenKind::LTEQ: {
    result.number = left <= right;
    break;
  }
  default: {
    result = left;
  }
  }
  return result;
}

RuntimeVal Interpreter::evaluateBinary(Expr *expr)
{
  BinaryExpr *bexpr = (BinaryExpr *)expr;
  RuntimeVal result;

  RuntimeVal left = this->evaluateTerm(bexpr->left);
  RuntimeVal right = {};
  if (bexpr->right)
    right = this->evaluateBinary(bexpr->right);

  switch (bexpr->oper.kind)
  {
  case TokenKind::PLUS: {
    result = left + right;
    break;
  }
  case TokenKind::MINUS: {
    result = left - right;
    break;
  }
  default: {
    result = left;
  }
  }
  return result;
}

RuntimeVal Interpreter::evaluateTerm(Expr *expr)
{
  BinaryExpr *bexpr = (BinaryExpr *)expr;
  RuntimeVal result = {};

  RuntimeVal left = this->evaluateUnary(bexpr->left);
  RuntimeVal right = {};
  if (bexpr->right)
    right = this->evaluateTerm(bexpr->right);

  switch (bexpr->oper.kind)
  {
  case TokenKind::ASTERISK: {
    result = left * right;
    break;
  }
  case TokenKind::SLASH: {
    if (right.number == 0)
      _logger.panic("Dividing by 0 is not allowed");
    result = left / right;
    break;
  }
  default: {
    result = left;
  }
  }
  return result;
}

RuntimeVal Interpreter::evaluateUnary(Expr *expr)
{
  UnaryExpr *uexpr = (UnaryExpr *)expr;

  RuntimeVal right = this->evaluatePrimary(uexpr->right);

  if (uexpr->oper.kind == TokenKind::MINUS)
    right.number *= -1;

  return right;
}

RuntimeVal Interpreter::evaluatePrimary(Expr *expr)
{
  PrimaryExpr *pexpr = (PrimaryExpr *)expr;
  RuntimeVal result = {};

  if (pexpr->expr != nullptr)
    return this->evaluate(pexpr->expr);

  switch (pexpr->value.kind)
  {
  case TokenKind::NUMBER: {
    result.setAsNumber(std::stod(pexpr->value.lexeme));
    break;
  }
  case TokenKind::STRING: {
    result.setAsString(pexpr->value.lexeme);
    break;
  }
  case TokenKind::IDENT: {
    if (this->variables.find(pexpr->value.lexeme) == this->variables.end())
      _logger.panic("Use of undeclared variable : " + pexpr->value.lexeme);
    return this->variables.find(pexpr->value.lexeme)->second;
    break;
  }
  default:
    _logger.panic("Runtime error");
  }

  return result;
}

void Interpreter::dumpVars()
{
  _logger.debug("VARIABLES DUMP");
  for (const auto &var : variables)
  {
    std::cout << var.first << /* " : " << (var.second).print() <<*/ '\n';
  }
}
