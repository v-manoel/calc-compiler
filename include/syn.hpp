#ifndef SYN_HPP
#define SYN_HPP

#include <map>
#include "token.hpp"
#include "fileHandler.hpp"
#include <stack>

enum ProductionType
{
  EXP,
  TERM,
  OPER1,
  OPER2,
  OPER3,
  NUM,
  FUNC,
  FUNC1,
  FUNC2
};

// Stack Definitions
enum SymbolType
{
  TERMINAL,
  NON_TERMINAL
};

struct Symbol
{
  int symbol;
  SymbolType type;
  Symbol(const int _symbol, const SymbolType _type) : symbol(_symbol), type(_type) {}
};

using namespace std;
class Syn
{
private:
  stack<Symbol> ll1_stack;
  map<ProductionType, map<TokenType, int>> parserTable;
  TknHandler tkn_handler;

public:
  Syn();
  Syn(const string &);
  ~Syn();
  void parser();
  inline Token* getNextToken() { return tkn_handler.getToken(); }
};

#endif