#include <ostream>
#include "../include/lex.hpp"
#include "../include/fileHandler.hpp"
#include "../include/compilerException.hpp"
#include "../include/syn.hpp"

int main(int argc, char *argv[])
{
  Lex *scanner;
  string inputFile = argv[1];
  string outputFile = argc > 2 ? argv[2] : argv[1];
  try
  {
    scanner = new Lex(inputFile, outputFile);
    scanner->scanner();
    scanner->~Lex();

    Syn *parser;
    parser = new Syn(outputFile);
    parser->parser();
    parser->~Syn();
  }
  catch (LexException e)
  {
    cout << e.what() << endl;
  }
  catch (SynException e)
  {
    cout << e.what() << endl;
  }

  return 0;
}
