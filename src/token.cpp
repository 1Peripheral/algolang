#include "../include/token.h"

Token::Token()
{
}

Token::Token(TokenKind kind, std::string lexeme)
{
  this->kind = kind;
  this->lexeme = lexeme;
}

void Token::set(TokenKind kind, std::string lexeme)
{
  this->kind = kind;
  this->lexeme = lexeme;
}

void Token::set(TokenKind kind, char lexeme)
{
  this->kind = kind;
  this->lexeme = std::string(lexeme, 1);
}

void Token::set(TokenKind kind)
{
  this->kind = kind;
}

void Token::set(std::string lexeme)
{
  this->lexeme = lexeme;
}

std::string Token::toString()
{
  if (this->kind == NUMBER || this->kind == IDENT)
    return kindStringRepr.find(this->kind)->second + "( " + this->lexeme + " )";
  return kindStringRepr.find(this->kind)->second;
}

TokenKind Token::checkIfKeyword(std::string str)
{
  Token token;
  for (auto iter = kindStringRepr.begin(); iter != kindStringRepr.end(); iter++)
  {
    if (iter->second == str)
      return iter->first;
  }
  return IDENT;
}
