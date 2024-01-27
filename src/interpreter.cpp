#include "../include/interpreter.h"

Interpreter::Interpreter(AST program) {
   this->program = program;
}

void Interpreter::run() {}

void Interpreter::traverse() {
   for (Stmnt stmnt : program.stmnts) {
      this->evaluate(stmnt);
   }
}

void Interpreter::evaluate(Stmnt stmnt) {
   std::cout << program.stmnts[0].type << std::endl;
   stmnt.print();
}