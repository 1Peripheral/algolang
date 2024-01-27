#pragma once

#include "ast.h"

class Interpreter {
public:
   Interpreter(AST program);
   
   void run();
   void traverse();
   void evaluate(Stmnt *stmnt);
   
private:
   AST program;
};
