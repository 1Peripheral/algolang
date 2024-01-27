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
   /* ENDIF = 105, */
   END = 105,
   WHILE = 106,
   /* ENDWHILE =  */
   REPEAT = 107,

   // Operators
   EQ = 200,
   EQEQ = 201,
   NOTEQ = 202,
   GT = 203,
   GTEQ = 204,
   LT = 205,
   LTEQ = 206,
   PLUS = 207,
   MINUS = 208,
   SLASH = 209,
   ASTERISK =210,
   LEFTPAR = 211,
   RIGHTPAR = 212, 
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
