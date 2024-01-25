#include <iostream>
#include "../include/lexer.h"

int main(void) {
   std::string source = "if foo > bar then var max = foo end";
   Lexer lex = Lexer(source);

   Token token;
   while (lex.peek() != '\0') {
      token = lex.nextToken();
      std::cout << token.toString() << std::endl;
   }

   return 0;
}
