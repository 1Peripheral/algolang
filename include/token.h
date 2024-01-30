#pragma once

#include <map>
#include <string>

enum TokenKind {
   ENDOF = -2,
   NEWLINE = -1,

   // Types
   NONE = 0,
   IDENT = 1,
   NUMBER = 2,
   STRING = 3,
   
   // KEYWORDS;
   VAR = 100,
   WRITE = 101,
   READ = 102,
   IF = 103,
   THEN = 104,
   END = 105,
   WHILE = 106,
   REPEAT = 107,
   CONTINUE = 108,
   BREAK = 109,

   // Operators
   AND = 200,
   OR = 201,
   EQ = 202,
   EQEQ = 203,
   NOTEQ = 204,
   GT = 205,
   GTEQ = 206,
   LT = 207,
   LTEQ = 208,
   PLUS = 209,
   MINUS = 210,
   SLASH = 211,
   ASTERISK =212,
   LEFTPAR = 213,
   RIGHTPAR = 214, 
};

class Token {
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
   
   {VAR, "var"},
   {WRITE, "write"},
   {READ, "read"},
   {IF, "if"},
   {THEN, "then"},
   {END, "end"},
   {WHILE, "while"},
   {REPEAT, "repeat"},
   {CONTINUE, "continue"},
   {BREAK, "break"},

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
};
