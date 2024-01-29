#include "../include/parser.h"

Parser::Parser(Lexer lexer) : lexer(lexer) {
   this->nextToken();
   this->nextToken();
}

AST Parser::program() {
   while (this->checkToken(NEWLINE))
      this->nextToken();

   while (!this->checkToken(ENDOF))
      ast.addStmnt(this->statement());
      /* this->statement(); */

   return this->ast;
}

Stmnt* Parser::statement() {
   Stmnt* stmnt;
   if (this->checkToken(WRITE)) {
      WriteStmnt* writeStmnt = new WriteStmnt();
      this->nextToken();
      if (this->checkToken(STRING)) {
         writeStmnt->stringLiteral = std::string(this->curToken.lexeme);
         this->nextToken();
      }
      else {
         writeStmnt->stringLiteral = "";
         writeStmnt->expr = this->expression();
      }
      stmnt = writeStmnt;
   }
   else if (this->checkToken(READ)) {
      this->nextToken();
      Token var = this->curToken;
      this->match(IDENT);
      stmnt = new ReadStmnt(var);
   }
   else if (this->checkToken(IF)) {
      IfStmnt* ifStmnt = new IfStmnt();
      this->nextToken();
      ifStmnt->expr = this->comparison();
   
      this->match(THEN);
      this->newLine();
   
      while (!this->checkToken(END)) {
         ifStmnt->stmnts.push_back(this->statement());
      }
      this->match(END);
      stmnt = ifStmnt;
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
      VarStmnt* varStmnt = new VarStmnt(); 
      this->nextToken();

      Token ident = this->curToken;
      this->match(IDENT);
      this->match(EQ);

      varStmnt->ident = ident;
      varStmnt->value = this->expression();
      stmnt = varStmnt;
   }
   else {
      _logger.panic("Syntax error at : " + this->curToken.lexeme);
   }
   this->newLine();
   return stmnt;
}

Expr* Parser::comparison() {
   BinaryExpr* expr = new BinaryExpr();
   expr->left = this->expression();
   while (this->isComparisonOperator()) {
      expr->oper = this->curToken;
      this->nextToken();
      expr->right = this->expression();
   }

   return expr;
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
   PrimaryExpr pexpr;

   if (this->checkToken(IDENT)) {
      pexpr.value = this->curToken;
      this->nextToken();
   }
   else if (this->checkToken(NUMBER)) {
      pexpr.value = this->curToken;
      this->nextToken();
   }
   else if (this->checkToken(LEFTPAR)) {
      this->nextToken();
      pexpr.value = Token(NONE, "");
      pexpr.expr = this->expression();
      this->match(RIGHTPAR);
   }
   else {
      _logger.panic("Expected operator operator at " + this->curToken.lexeme);
   }
   
   return pexpr;
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
