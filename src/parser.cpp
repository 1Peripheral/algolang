#include "../include/parser.h"

Parser::Parser(Lexer lexer) : lexer(lexer) {
   this->nextToken();
   this->nextToken();
}

void Parser::program() {
   std::cout << "PROGRAM" << std::endl;

   while (this->checkToken(NEWLINE))
      this->nextToken();

   while (!this->checkToken(ENDOF))
      this->statement();
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
      this->nextToken();
      this->match(IDENT);
      this->match(EQ);
      this->expression();
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

void Parser::expression() {
   std::cout << "EXPRESSION" << std::endl;
   this->term();
   while (this->checkToken(PLUS) || this->checkToken(MINUS)) {
      this->nextToken();
      this->term();
   }
}

void Parser::term() {
   std::cout << "TERM" << std::endl;
   this->unary();
   while (this->checkToken(ASTERISK) || this->checkToken(SLASH)) {
      this->nextToken();
      this->unary();
   }
}

void Parser::unary() {
   std::cout << "UNARY" << std::endl;
   if (this->checkToken(PLUS) || this->checkToken(MINUS)) this->nextToken();
   this->primary();
}

void Parser::primary() {
   std::cout << "PRIMARY (" << this->curToken.lexeme << ")" << std::endl;
   if (this->checkToken(IDENT)) {
      this->nextToken();
   }
   else if (this->checkToken(NUMBER)) {
      this->nextToken();
   }
   else {
      _logger.panic("Expected operator operator at " + this->curToken.lexeme);
   }
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
