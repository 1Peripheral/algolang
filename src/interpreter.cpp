#include "../include/interpreter.h"

Interpreter::Interpreter(AST program) {
   this->program = program;
   this->breakLoopFlag = false;
   this->continueLoopFlag = false;
}

void Interpreter::run() {
   this->run(program.stmnts);
}

void Interpreter::run(std::vector<Stmnt*> stmnts) {
   for (auto stmnt = stmnts.begin() ; stmnt != stmnts.end() ; stmnt++) {
      switch ((*stmnt)->type) {
         case VARSTMNT: {
            VarStmnt* varStmnt = (VarStmnt*) *stmnt;
            this->variables[varStmnt->ident.lexeme] = this->evaluate(varStmnt->value);
            break;
         } 
         case WRITESTMNT : {
            // TODO : String concatenation (eg : write "Hello" + "world" + x)
            WriteStmnt* writeStmnt = (WriteStmnt*) *stmnt;
            if (writeStmnt->expr != nullptr) {
               std::cout << this->evaluate(writeStmnt->expr) << std::endl;
            }
            else {
               std::cout << writeStmnt->stringLiteral << std::endl; 
            }
            break;
         }
         case READSTMNT : {
            ReadStmnt* readStmnt = (ReadStmnt*) *stmnt;
            RuntimeVal tmp;
            std::cin >> tmp;
            this->variables[readStmnt->variable.lexeme] = tmp;
            break;
         }
         case IFSTMNT : {
            IfStmnt* ifStmnt = (IfStmnt*) *stmnt;
            RuntimeVal comparisonResult = this->evaluateComparison(ifStmnt->expr);
            if (comparisonResult) {
               this->run(ifStmnt->stmnts);
            }
            break;
         }
         case WHILESTMNT: {
            WhileStmnt* whileStmnt = (WhileStmnt*) *stmnt;
            RuntimeVal comparisonResult = this->evaluateComparison(whileStmnt->expr);
            if (!comparisonResult) break;
            this->run(whileStmnt->stmnts);
            if (breakLoopFlag) {
               breakLoopFlag = false;
               break;
            }
            stmnt--; // decrementing the iterator in order to re evaluate the while comparison.

            break;
         }
         case CONTINUESTMNT : {
            continueLoopFlag = true;
            break;
         }
         case BREAKSTMNT : {
            breakLoopFlag = true;
            break;
         }
         default: {}
      }
   }
}

RuntimeVal Interpreter::evaluate(Expr* expr) {
   RuntimeVal result = 0; // Will be initialized with None when types are implemented
   switch(expr->type) {
      case BINARYEXPR : {
         result = this->evaluateBinary(expr);
         break;
      }
      default : {
         result = 0;
         break;
      }
   }
   
   return result;
}

RuntimeVal Interpreter::evaluateComparison(Expr* expr) {
   BinaryExpr* bexpr = (BinaryExpr*)expr;
   RuntimeVal result;

   RuntimeVal left = this->evaluateBinary(bexpr->left);
   RuntimeVal right = {};
   if (bexpr->right)
      right = this->evaluateComparison(bexpr->right);

   switch (bexpr->oper.kind) {
      case TokenKind::EQEQ : {
         result = left == right;
         break;
      }
      case TokenKind::GT : {
         result = left > right;
         break;
      }
      case TokenKind::GTEQ : {
         result = left >= right;
         break;
      }
      case TokenKind::LT : {
         result = left < right;
         break;
      }
      case TokenKind::LTEQ : {
         result = left <= right;
         break;
      }
      default: {
         result = left;
      }
   }
   return result;
   
}

RuntimeVal Interpreter::evaluateBinary(Expr* expr) {
   BinaryExpr* bexpr = (BinaryExpr*)expr;
   RuntimeVal result;

   RuntimeVal left = this->evaluateTerm(bexpr->left);
   RuntimeVal right = {};
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
   RuntimeVal right= {};
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
   
   if (pexpr->expr != nullptr)
      return this->evaluate(pexpr->expr);

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
