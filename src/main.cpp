#include <ostream>
#include "../include/lex.hpp"
#include "../include/fileHandler.hpp"
#include "../include/syn.hpp"

int main(int argc, char *argv[])
{
  Lex *scanner;
  string inputFile = argv[1];
  string outputFile = argc > 2 ? argv[2] : argv[1];
  scanner = new Lex(inputFile, outputFile);

  scanner->scanner();
  scanner->~Lex();
  
  Syn *parser;
  parser = new Syn(outputFile);
  parser->parser();
  parser->~Syn();
  // cout << "Teste" << endl;
  // TknHandler tkn_handler(outputFile);
  // cout << *tkn_handler.getToken() << endl;

  return 0;
}

// ./compc expressao.comp

// lex <- expressao.comp <- expressao.tkn
// syn <- expressao.tkn <- bool (true | false)