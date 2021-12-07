#ifndef COMPILEREXECPTION_HPP
#define COMPILEREXECPTION_HPP
#include <iostream>
#include <exception>
#include <sstream>
#include <string>
#include "position.hpp"
#include "token.hpp"

using namespace std;
class LexException : public exception
{
private:
  Position pos;
  string lexem;
  string expected;

public:
  LexException(const Position &_pos, const string &_lexem, const string &_expected)
      : pos(_pos), lexem(_lexem), expected(_expected) {}
  const char *what() const throw()
  {
    stringstream error_desc;
    error_desc << "(LEXICAL ERROR) in " << pos << ": expected " << expected << "but given " << lexem << endl;
    return (error_desc.str()).c_str();
  }
  virtual ~LexException() = default;
};

class SynException : public exception
{
private:
  Token tkn;
  TokenType expected;

public:
  SynException(const Token &_tkn, const TokenType &_tkn_type)
      : tkn(_tkn), expected(_tkn_type) {}
  const char *what() throw()
  {
    stringstream error_desc;
    error_desc << "(SYNTATIC ERROR) in " << tkn.getPosition() << ": expected " << Token::toString(expected) << "but given " << tkn.getlexem() << " of type " << Token::toString(tkn.getType()) << endl;
    return (error_desc.str()).c_str();
  }
  virtual ~SynException() = default;
};

#endif