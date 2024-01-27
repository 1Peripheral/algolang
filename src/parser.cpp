#include "../include/parser.h"

Parser::Parser(Lexer lexer) : lexer(lexer) {
   this->nextToken();
   this->nextToken();
}

AST Parser::program() {
   std::cout << "PROGRAM" << std::endl;

   while (this->checkToken(NEWLINE))
      this->nextToken();

   while (!this->checkToken(ENDOF))
      this->statement();

   return this->ast;
}

void Parser::statement() {
   if (this->checkToken(WRITE)) {
      std::cout << "STATEMENT-WRITE" << std::endl;
      this->nextToken();
      if (this->checkToken(STRING)) {
         this->nextToken();
      }
      else {
         this->expression();
      }
   }
   else if (this->checkToken(READ)) {
      std::cout << "STATEMENT-READ" << std::endl;
      this->nextToken();
      this->match(IDENT);
   }
   else if (this->checkToken(IF)) {
      std::cout << "STATEMENT-IF" << std::endl;
      this->nextToken();
      this->comparison();
   
      this->match(THEN);
      this->newLine();
   
      while (!this->checkToken(END))
         this->statement();
      this->match(END);
   }
   else if (this->checkToken(WHILE)) {
      std::cout << "STATEMENT-WHILE" << std::endl;
      this->nextToken();
      this->comparison();
   
      this->match(REPEAT);
      this->newLine();
   
      while (!this->checkToken(END))
         this->statement();
   
      this->match(END);
   }
   else if (this->checkToken(VAR)) {
      VarStmnt stmnt; 
      std::cout << "STATEMENT-VAR" << std::endl;
      this->nextToken();

      Token ident = this->curToken;
      this->match(IDENT);
      this->match(EQ);

      stmnt.value = this->expression();
      ast.addStmnt(stmnt);
   }
   else {
      _logger.panic("Syntax error at : " + this->curToken.lexeme);
   }
   
   this->newLine();
}

void Parser::comparison() {
   std::cout << "COMPARISON" << std::endl;
   this->expression();
   
   if (this->isComparisonOperator()) {
      this->nextToken();
      this->expression();
   }
   else {
      _logger.panic("Expected operator operator at " + this->curToken.lexeme + " .");
   }

   while (this->isComparisonOperator()) {
      this->nextToken();
      this->expression();
   }
}

Expr Parser::expression() {
   std::cout << "EXPRESSION" << std::endl;
   BinaryExpr expr;
   expr.left = this->term();
   while (this->checkToken(PLUS) || this->checkToken(MINUS)) {
      expr.oper = this->curToken;
      this->nextToken();
      expr.right = this->term();
   }

   return expr; 
}

BinaryExpr Parser::term() {
   std::cout << "TERM" << std::endl;
   BinaryExpr expr;
   expr.left = this->unary();
   while (this->checkToken(ASTERISK) || this->checkToken(SLASH)) {
      expr.oper = this->curToken;
      this->nextToken();
      expr.right = this->unary();
   }

   return expr;
}

UnaryExpr Parser::unary() {
   std::cout << "UNARY" << std::endl;
   UnaryExpr expr;
   if (this->checkToken(PLUS) || this->checkToken(MINUS)) {
      expr.oper = this->curToken;
      this->nextToken();
   }
   else 
      expr.oper = Token(NONE, "");

   expr.right = this->primary();
   return expr;
}

PrimaryExpr Parser::primary() {
   std::cout << "PRIMARY (" << this->curToken.lexeme << ")" << std::endl;
   PrimaryExpr expr;

   if (this->checkToken(IDENT)) {
      expr.value = this->curToken;
      this->nextToken();
   }
   else if (this->checkToken(NUMBER)) {
      expr.value = this->curToken;
      this->nextToken();
   }
   else {
      _logger.panic("Expected operator operator at " + this->curToken.lexeme);
   }
   
   return expr;
}

void Parser::newLine() {
   std::cout << "NEWLINE" << std::endl;

   this->match(NEWLINE);
   while (this->checkToken(NEWLINE)) this->nextToken();
}

void Parser::nextToken() {
   this->curToken = peekToken;
   this->peekToken = this->lexer.nextToken();
}

void Parser::match(TokenKind kind) {
   if (!this->checkToken(kind))
      _logger.panic("Expected " + kindStringRepr.at(kind) + " got " + this->curToken.lexeme);

   this->nextToken();
}

bool Parser::checkToken(TokenKind kind) {
   return this->curToken.kind == kind;
}

bool Parser::checkPeek(TokenKind kind) {
   return this->peekToken.kind == kind;
}

bool Parser::isComparisonOperator() {
   return checkToken(EQEQ) || checkToken(NOTEQ) ||
      checkToken(GT) || checkToken(GTEQ) ||
      checkToken(LT) || checkToken(LTEQ);
}
