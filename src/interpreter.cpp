#include "../include/interpreter.h"

Interpreter::Interpreter(AST program) {
   this->program = program;
}

void Interpreter::run() {
   for (Stmnt* stmnt : program.stmnts) {
      switch (stmnt->type) {
         case VARSTMNT: {
            VarStmnt* varStmnt = (VarStmnt*) stmnt;
            this->variables.insert({
               varStmnt->ident.lexeme, 
               this->evaluate(varStmnt->value)
            });
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
      case UNARYEXPR : {
         result = this->evaluateUnary(expr);
         break;
      }
      case PRIMARYEXPR : {
         result = this->evaluatePrimary((PrimaryExpr*)expr);
         break;
      }
      default : {}
   }
   
   return result;
}

RuntimeVal Interpreter::evaluateBinary(Expr* expr) {
   BinaryExpr* bexpr = (BinaryExpr*)expr;
   RuntimeVal result;

   RuntimeVal left = this->evaluate(bexpr->left);
   /* RuntimeVal right; */
   /* if (bexpr->right) */
   /*    right = this->evaluate(bexpr->right); */

   switch (bexpr->oper.kind) {
      case TokenKind::PLUS : {
         result = left;
         break;
      }
      case TokenKind::MINUS : {
         result = left;
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
         std::cout << result << std::endl;
         break;
      }
      case TokenKind::IDENT : {
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
