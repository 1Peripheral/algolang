#include "../include/parser.h"

Parser::Parser(Lexer lexer) : lexer(lexer) {
   lexer.nextToken();
   lexer.nextToken();
}

void Parser::program() {
   std::cout << "PROGRAM" << std::endl;
   while (!this->checkToken(ENDOF))
      this->statement();
}

void Parser::nextToken() {
   this->curToken = peekToken;
   this->peekToken = this->lexer.nextToken();
}

void Parser::match(TokenKind kind) {
   if (!this->checkToken(kind))
      _logger.panic("Expected " + kindStringRepr.at(kind) + " got " + this->curToken.lexeme + " .");

   this->nextToken();
}

bool Parser::checkToken(TokenKind kind) {
   return this->curToken.kind == kind;
}

bool Parser::checkPeek(TokenKind kind) {
   return this->peekToken.kind == kind;
}
