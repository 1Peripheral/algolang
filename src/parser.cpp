#include "../include/parser.h"

Parser::Parser(Lexer lexer) : lexer(lexer) {
   this->nextToken();
   this->nextToken();
}

AST Parser::program() {
   while (this->checkToken(NEWLINE))
      this->nextToken();

   while (!this->checkToken(ENDOF))
      this->statement();

   return this->ast;
}

void Parser::statement() {
   if (this->checkToken(WRITE)) {
      this->nextToken();
      if (this->checkToken(STRING)) {
         this->nextToken();
      }
      else {
         this->expression();
      }
   }
   else if (this->checkToken(READ)) {
      this->nextToken();
      this->match(IDENT);
   }
   else if (this->checkToken(IF)) {
      this->nextToken();
      this->comparison();
   
      this->match(THEN);
      this->newLine();
   
      while (!this->checkToken(END))
         this->statement();
      this->match(END);
   }
   else if (this->checkToken(WHILE)) {
      this->nextToken();
      this->comparison();
   
      this->match(REPEAT);
      this->newLine();
   
      while (!this->checkToken(END))
         this->statement();
   
      this->match(END);
   }
   else if (this->checkToken(VAR)) {
      VarStmnt* stmnt = new VarStmnt(); 
      this->nextToken();

      Token ident = this->curToken;
      this->match(IDENT);
      this->match(EQ);

      stmnt->ident = ident;
      stmnt->value = this->expression();
      ast.addStmnt(stmnt);
   }
   else {
      _logger.panic("Syntax error at : " + this->curToken.lexeme);
   }
   this->newLine();
}

void Parser::comparison() {
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

Expr* Parser::expression() {
   BinaryExpr* expr = new BinaryExpr();
   expr->left = this->term();
   while (this->checkToken(PLUS) || this->checkToken(MINUS)) {
      expr->oper = this->curToken;
      this->nextToken();
      expr->right = this->expression();
   }

   return expr; 
}

BinaryExpr* Parser::term() {
   BinaryExpr* expr = new BinaryExpr();
   expr->left = this->unary();
   while (this->checkToken(ASTERISK) || this->checkToken(SLASH)) {
      expr->oper = this->curToken;
      this->nextToken();
      expr->right = this->term();
   }

   return expr;
}

UnaryExpr* Parser::unary() {
   UnaryExpr* expr = new UnaryExpr();
   if (this->checkToken(PLUS) || this->checkToken(MINUS)) {
      expr->oper = this->curToken;
      this->nextToken();
   }
   else 
      expr->oper = Token(NONE, "");

   expr->right = this->primary();
   return expr;
}

PrimaryExpr Parser::primary() {
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
