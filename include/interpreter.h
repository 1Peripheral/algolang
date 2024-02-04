#pragma once

#include <unordered_map>

#include "ast.h"
#include "logger.h"
#include "runtimeval.h"

class Interpreter
{
public:
  Interpreter(AST program);

  void run();
  void run(std::vector<Stmnt *> stmnts);
  void traverse();
  RuntimeVal evaluate(Expr *expr);
  RuntimeVal evaluateComparison(Expr *expr);
  RuntimeVal evaluateBinary(Expr *expr);
  RuntimeVal evaluateTerm(Expr *expr);
  RuntimeVal evaluateUnary(Expr *expr);
  RuntimeVal evaluatePrimary(PrimaryExpr *expr);
  void dumpVars();

private:
  AST program;
  std::unordered_map<std::string, RuntimeVal> variables;
  Logger _logger;
  int conditionFlag;
  bool breakLoopFlag;
  bool continueLoopFlag;
};
