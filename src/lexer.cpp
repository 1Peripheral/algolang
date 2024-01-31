#include "../include/lexer.h"
#include <cctype>

static std::string toString(char c);

std::unordered_map<char, Alphabet> Lexer::alphabetDict;

void Lexer::initDict() {
   if (alphabetDict.find(',') != alphabetDict.end()) { return; }
   alphabetDict['(']    = Alphabet::OPEN_BRACE;
   alphabetDict[')']    = Alphabet::CLOSE_BRACE;
   alphabetDict['}']    = Alphabet::OPEN_CURLY_BRACE;
   alphabetDict['{']    = Alphabet::CLOSE_CURLY_BRACE;
   alphabetDict[',']    = Alphabet::COMMA;
   alphabetDict['\"']   = Alphabet::QUOTE;
   alphabetDict['-']    = Alphabet::MINUS;
   alphabetDict['+']    = Alphabet::PLUS;
   alphabetDict['*']    = Alphabet::ASTERISK;
   alphabetDict['/']    = Alphabet::SLASH;
   alphabetDict['>']    = Alphabet::GT;
   alphabetDict['<']    = Alphabet::LT;
   alphabetDict['=']    = Alphabet::EQUAL;
   alphabetDict['!']    = Alphabet::EXCLAMATION;
   alphabetDict['\n']   = Alphabet::ENDLINE;
   alphabetDict['\0']   = Alphabet::NULLCHAR;

   for (char c = '0'; c < '9'; ++c) {
      alphabetDict[c] = Alphabet::NUMBER;
   }
   for (char c = 'A'; c < 'z'; ++c) {
      alphabetDict[c] = Alphabet::ALPHA;
   }
}


Lexer::Lexer(std::string source) {
   this->source = source + "\n"; 
   this->curChar = ' ';
   this->curIndex = -1;
   this->nextChar();
   Lexer::initDict();
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
   switch ( Lexer::alphabetDict[this->curChar]) {
      case Alphabet::ENDLINE:
         token.set(NEWLINE, this->curChar);
         break;
      case Alphabet::NULLCHAR:
         token.set(ENDOF, this->curChar);
         break;
      case Alphabet::PLUS :
         token.set(PLUS, this->curChar);
         break;
      case Alphabet::MINUS :
         token.set(MINUS, this->curChar);
         break;
      case Alphabet::SLASH:
         token.set(SLASH, this->curChar);
         break;
      case Alphabet::ASTERISK:
         token.set(ASTERISK, this->curChar);
         break;
      case Alphabet::OPEN_BRACE : {
         token.set(LEFTPAR, this->curChar);
         break;
      }
      case Alphabet::CLOSE_BRACE : {
         token.set(RIGHTPAR, this->curChar);
         break;
      }
      case Alphabet::EQUAL : {
         if (this->peek() == '=') {
            this->nextChar();
            token.set(EQEQ, "==");
         }
         else token.set(EQ, "=");
         break;
      }
      case Alphabet::EXCLAMATION : {
         if (this->peek() == '=') {
            this->nextChar();
            token.set(NOTEQ, "!=");
         }
         else 
            _logger.panic("Expected != got !" + toString(this->curChar) + " .");
         break;
      }
      case Alphabet::GT : {
         if (this->peek() == '=') {
            this->nextChar();
            token.set(GTEQ, ">=");
         }
         else 
            token.set(GT, ">");
         break;
      }
      case Alphabet::LT : {
         if (this->peek() == '=') {
            this->nextChar();
            token.set(LTEQ, "<=");
         }
         else 
            token.set(LT, "<");
         break;
      }
      case Alphabet::QUOTE : {
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
      case Alphabet::NUMBER : {
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
      case Alphabet::ALPHA : {
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
