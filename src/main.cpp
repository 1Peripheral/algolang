#include <fstream>
#include <sstream>
#include "../include/lexer.h"
#include "../include/parser.h"

int main(int argc, char** argv) {
   Logger logger;
   std::string source;
   if (argc < 2) {
      logger.info("You must provide a source file .");
      exit(1);
   }
   else {
      std::ifstream sourceFile(argv[1]); 
      std::stringstream sourceStream;
      sourceStream << sourceFile.rdbuf();
      source = sourceStream.str();
   }

   Lexer lex = Lexer(source);
   Parser parser = Parser(lex);

   parser.program();

   /* while (lex.peek() != '\0') { */
   /*    std::cout << lex.nextToken().toString() << std::endl; */
   /* } */

   return 0;
}
