#pragma once

#include <map>
#include <string>

enum TokenKind
{
  ENDOF,
  NEWLINE,

  // Types
  NONE,
  IDENT,
  NUMBER,
  STRING,
  ARRAY,

  // KEYWORDS;
  LET,
  WRITE,
  AS,
  READ,
  IF,
  THEN,
  END,
  WHILE,
  REPEAT,
  CONTINUE,
  BREAK,
  FN,
  RETURN,

  // Operators
  AND,
  OR,
  EQ,
  EQEQ,
  NOTEQ,
  GT,
  GTEQ,
  LT,
  LTEQ,
  PLUS,
  MINUS,
  SLASH,
  ASTERISK,
  LEFTPAR,
  RIGHTPAR,
  LEFTBRAC,
  RIGHTBRAC,
  COMMA,
};

class Token
{
public:
  Token();
  Token(TokenKind kind, std::string lexeme);

  void set(TokenKind kind, std::string lexeme);
  void set(TokenKind kind, char lexeme);
  void set(TokenKind kind);
  void set(std::string lexeme);
  static TokenKind checkIfKeyword(std::string str);

  std::string toString();

public:
  TokenKind kind;
  std::string lexeme;
};

const std::map<TokenKind, std::string> kindStringRepr = {
    {ENDOF, "endof"},
    {NEWLINE, "newline"},

    {IDENT, "ident"},
    {NUMBER, "number"},
    {STRING, "string"},

    {LET, "let"},
    {WRITE, "write"},
    {AS, "as"},
    {READ, "read"},
    {IF, "if"},
    {THEN, "then"},
    {END, "end"},
    {WHILE, "while"},
    {REPEAT, "repeat"},
    {CONTINUE, "continue"},
    {BREAK, "break"},
    {FN, "fn"},
    {RETURN, "return"},

    {AND, "and"},
    {OR, "or"},
    {EQ, "eq"},
    {EQEQ, "eqeq"},
    {NOTEQ, "noteq"},
    {GT, "gt"},
    {GTEQ, "gteq"},
    {LT, "lt"},
    {LTEQ, "lteq"},
    {PLUS, "plus"},
    {MINUS, "minus"},
    {SLASH, "slash"},
    {ASTERISK, "asterisk"},
    {LEFTPAR, "leftpar"},
    {RIGHTPAR, "rightpar"},
    {COMMA, ","},
    {LEFTBRAC, "leftbrac"},
    {RIGHTBRAC, "rightbrac"},
};
