#pragma once

#include <unordered_map>

#include "ast.h"
#include "logger.h"
#include "runtimeval.h"
#include "frame.h"

class Interpreter
{
public:
  Interpreter();
  Interpreter(AST program);

  void traverse();
  void traverse(std::vector<Stmnt *> stmnts);
  void run(AST program);
  RuntimeVal evaluate(Expr *expr);
  RuntimeVal evaluateComparison(Expr *expr);
  RuntimeVal evaluateBinary(Expr *expr);
  RuntimeVal evaluateTerm(Expr *expr);
  RuntimeVal evaluateUnary(Expr *expr);
  RuntimeVal evaluatePrimary(Expr *expr);
  void dumpVars();

private:
  AST program;
  // std::unordered_map<std::string, RuntimeVal> variables;
  StackFrame frames;
  std::unordered_map<std::string, FunctionDecl> functions;
  Logger _logger;
  int conditionFlag;
  bool breakLoopFlag;
  bool continueLoopFlag;
};
