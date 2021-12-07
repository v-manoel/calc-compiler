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
      "TK_COS",
      "TK_SIN",
      "TK_ROUND",
      "TK_ABS",
      "TK_SQRT",
      "TK_TAN",
      "TK_LOG",
      "TK_PI",
      "TK_E"};
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
      "TK_COS",
      "TK_SIN",
      "TK_ROUND",
      "TK_ABS",
      "TK_SQRT",
      "TK_TAN",
      "TK_LOG",
      "TK_PI",
      "TK_E"};

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

ostream &operator<<(ostream &os, const TokenType &tkn_type)
{
  vector<string> tkn_types = {
      "TK_NUMBER",
      "TK_SEPARATOR",
      "TK_END_DELIMITER",
      "TK_BEG_DELIMITER",
      "TK_OPERATOR_L1",
      "TK_OPERATOR_L2",
      "TK_OPERATOR_L3",
      "TK_COS",
      "TK_SIN",
      "TK_ROUND",
      "TK_ABS",
      "TK_SQRT",
      "TK_TAN",
      "TK_LOG",
      "TK_PI",
      "TK_E"};
      
  os << tkn_types.at(tkn_type);
  return os;
}