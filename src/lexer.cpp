#include "../include/lexer.h"
#include <cctype>

static std::string toString(char c);

Lexer::Lexer(std::string source) {
   this->source = source + "\n"; 
   this->curChar = ' ';
   this->curIndex = -1;
   this->nextChar();
}

void Lexer::nextChar() {
   this->curIndex++;
   if (this->curIndex >= (int)this->source.length())
      this->curChar = '\0';
   else 
      this->curChar = this->source.at(this->curIndex);
}

char Lexer::peek() {
   if (this->curIndex + 1 >= (int)this->source.length())
      return '\0';

   return this->source.at(this->curIndex + 1);
}

Token Lexer::nextToken() {
   this->skipWhiteSpace();
   this->skipComment();

   Token token;
   
   switch (this->curChar) {
      case '\n' :
         token.set(NEWLINE, this->curChar);
         break;
      case '\0' :
         token.set(ENDOF, this->curChar);
         break;
      case '+' :
         token.set(PLUS, this->curChar);
         break;
      case '-' :
         token.set(MINUS, this->curChar);
         break;
      case '/' :
         token.set(SLASH, this->curChar);
         break;
      case '*' :
         token.set(ASTERISK, this->curChar);
         break;
      case '(' : {
         token.set(LEFTPAR, this->curChar);
         break;
      }
      case ')' : {
         token.set(RIGHTPAR, this->curChar);
         break;
      }
      case '=' : {
         if (this->peek() == '=') {
            this->nextChar();
            token.set(EQEQ, "==");
         }
         else token.set(EQ, "=");
         break;
      }
      case '!' : {
         if (this->peek() == '=') {
            this->nextChar();
            token.set(NOTEQ, "!=");
         }
         else 
            _logger.panic("Expected != got !" + toString(this->curChar) + " .");
         break;
      }
      case '>' : {
         if (this->peek() == '=') {
            this->nextChar();
            token.set(GTEQ, ">=");
         }
         else 
            token.set(GT, ">");
         break;
      }
      case '<' : {
         if (this->peek() == '=') {
            this->nextChar();
            token.set(LTEQ, "<=");
         }
         else 
            token.set(LT, "<");
         break;
      }
      case '"' : {
         this->nextChar();
         int startIndex = this->curIndex;
         while (this->curChar != '"') {
            if (this->curChar == '\n')
               _logger.panic("Closing `\"` not found ");
            this->nextChar();
         }

         std::string str = this->source.substr(startIndex, this->curIndex - startIndex);
         token.set(STRING, str);
         break;
      }
      case '0'...'9' : {
         int startIndex = this->curIndex;
         while (isdigit(this->peek())) this->nextChar();
         if (this->peek() == '.') {
            this->nextChar();
            if (!isdigit(this->peek())) 
               _logger.panic("Illegal character after number literal .");
            while (isdigit(this->peek())) this->nextChar();
         }
         token.set(NUMBER, this->source.substr(startIndex, this->curIndex - startIndex + 1));
         break;
      }
      case 'A'...'z' : {
         int startIndex = this->curIndex;
         while (isalnum(this->peek()) || this->peek()== '_') this->nextChar();

         std::string str = this->source.substr(startIndex, this->curIndex - startIndex + 1);
         TokenKind kind_ = Token::checkIfKeyword(str);

         token.set(kind_, str);
         break;
      }
      default : {
         _logger.panic("Unknown symbol : " + toString(this->curChar));
      }
   }

   this->nextChar();
   return token;
}

void Lexer::skipWhiteSpace() {
   while (this->curChar == ' ' || this->curChar == '\t' ||
         this->curChar == '\r' ) 
      this->nextChar();
}

void Lexer::skipComment() {
   if (this->curChar == '#')
      while (this->curChar != '\n') this->nextChar();
}

static std::string toString(char c) {
   return std::string(c, 2);
}
