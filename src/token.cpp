#include "../include/token.hpp"
#include "../include/position.hpp"
#include <iostream>
#include <vector>

ostream &operator<<(ostream &os, const Token &tkn)
{
  const char *tkn_types[] = {
      "TK_NUMBER",
      "TK_SEPARATOR",
      "TK_END_DELIMITER",
      "TK_BEG_DELIMITER",
      "TK_OPERATOR_L1",
      "TK_OPERATOR_L2",
      "TK_OPERATOR_L3",
      "TK_FUNCTION_1",
      "TK_FUNCTION_2",
      "TK_CONST"};
  os << "<";
  os << "type: " << tkn_types[tkn.type] << " ";
  os << "lexem: " << tkn.lexem << " ";
  os << "pos: " << tkn.position << " ";
  os << ">" << endl;

  return os;
}

TokenType Token::toTokenType(const string &type_name)
{
  vector<string> tkn_types = {
      "TK_NUMBER",
      "TK_SEPARATOR",
      "TK_END_DELIMITER",
      "TK_BEG_DELIMITER",
      "TK_OPERATOR_L1",
      "TK_OPERATOR_L2",
      "TK_OPERATOR_L3",
      "TK_FUNCTION_1",
      "TK_FUNCTION_2",
      "TK_CONST"};

  TokenType tkn_type;
  for (size_t i = 0; i < tkn_types.size(); i++)
  {
    if (tkn_types[i] == type_name)
    {
      tkn_type = TokenType(i);
      return tkn_type;
    }
  }
  cout << "TokenType Conversion Error" << endl;
  exit(-1);
}