#include "../include/interpreter.h"

Interpreter::Interpreter(AST program) {
   this->program = program;
}

void Interpreter::run() {
   for (Stmnt* stmnt : program.stmnts) {
      switch (stmnt->type) {
         case VARSTMNT: {
            VarStmnt* varStmnt = (VarStmnt*) stmnt;
            this->variables[varStmnt->ident.lexeme] = this->evaluate(varStmnt->value);
            break;
         } 
         case WRITESTMNT : {
            // TODO : String concatenation (eg : write "Hello" + "world" + x)
            WriteStmnt* writeStmnt= (WriteStmnt*) stmnt;
            if (writeStmnt->expr != nullptr) {
               std::cout << this->evaluate(writeStmnt->expr) << std::endl;
            }
            else {
               std::cout << writeStmnt->stringLiteral << std::endl; 
            }
            break;
         }
         case READSTMNT : {
            ReadStmnt* readStmnt= (ReadStmnt*) stmnt;
            RuntimeVal tmp;
            std::cin >> tmp;
            this->variables[readStmnt->variable.lexeme] = tmp;
            break;
         }
         default: {}
      }
   }
}

RuntimeVal Interpreter::evaluate(Expr* expr) {
   RuntimeVal result;
   switch(expr->type) {
      case BINARYEXPR : {
         result = this->evaluateBinary(expr);
         break;
      }
      default : {}
   }
   
   return result;
}

RuntimeVal Interpreter::evaluateBinary(Expr* expr) {
   BinaryExpr* bexpr = (BinaryExpr*)expr;
   RuntimeVal result;

   RuntimeVal left = this->evaluateTerm(bexpr->left);
   RuntimeVal right;
   if (bexpr->right)
      right = this->evaluateBinary(bexpr->right);

   switch (bexpr->oper.kind) {
      case TokenKind::PLUS : {
         result = left + right;
         break;
      }
      case TokenKind::MINUS : {
         result = left - right;
         break;
      }
      default: {
         result = left;
      }
   }
   return result;
}

RuntimeVal Interpreter::evaluateTerm(Expr* expr) {
   BinaryExpr* bexpr = (BinaryExpr*)expr;
   RuntimeVal result;

   RuntimeVal left = this->evaluateUnary(bexpr->left);
   RuntimeVal right;
   if (bexpr->right)
      right = this->evaluateTerm(bexpr->right);

   switch (bexpr->oper.kind) {
      case TokenKind::ASTERISK : {
         result = left * right;
         break;
      }
      case TokenKind::SLASH : {
         if (right == 0)
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

RuntimeVal Interpreter::evaluateUnary(Expr* expr) {
   UnaryExpr* uexpr = (UnaryExpr*) expr;

   RuntimeVal right = this->evaluatePrimary(&uexpr->right);

   if (uexpr->oper.kind == TokenKind::MINUS)
      right *= -1;

   return right;
}

RuntimeVal Interpreter::evaluatePrimary(PrimaryExpr* expr) {
   PrimaryExpr* pexpr = (PrimaryExpr*) expr;
   RuntimeVal result = 0;

   switch (pexpr->value.kind) {
      case TokenKind::NUMBER : {
         result = std::stod(pexpr->value.lexeme);
         break;
      }
      case TokenKind::IDENT : {
         if (this->variables.find(pexpr->value.lexeme) == this->variables.end())
            _logger.panic("Use of ndeclared variable : " + pexpr->value.lexeme);
         return this->variables.find(pexpr->value.lexeme)->second;
         break;
      }
      default : {
         _logger.panic("Runtime error");
      }
   }

   return result;
}

void Interpreter::dumpVars() {
   _logger.debug("VARIABLES DUMP");
   for (const auto& var : variables) {
      std::cout << var.first << " : " << var.second << std::endl;
   }
}
