#include <fstream>
#include <sstream>
#include <string>

#include "../include/interpreter.h"
#include "../include/lexer.h"
#include "../include/parser.h"

int main(int argc, char **argv)
{
  Logger logger;
  std::string source;
  Interpreter interpreter;
  if (argc < 2)
  {
    std::cout << "Algolang REPL"  << '\n';
    std::string input = "";
    while (true) {
      std::cout << "(al) #> ";
      std::getline(std::cin, input);
      if (input == ".exit") 
        return 0;
      else {
        AST program = Parser(Lexer(input)).parse();
        interpreter.run(program);
      }
    }
    return 0;
  }
  std::ifstream sourceFile(argv[1]);
  std::stringstream sourceStream;
  sourceStream << sourceFile.rdbuf();
  source = sourceStream.str();

  Lexer lex = Lexer(source);
  Parser parser = Parser(lex);

  interpreter.run(parser.parse());

  return 0;
}
