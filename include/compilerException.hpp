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
  string message;

public:
  LexException(const Position &_pos, const string &_lexem, const string &_expected)
      : pos(_pos), lexem(_lexem), expected(_expected)
  {
    stringstream error_desc;
    error_desc << "(LEXICAL ERROR) in " << pos << ": expected " << expected << " but given " << lexem << endl;
    message = error_desc.str();
  }
  const char *what() const throw()
  {
    return message.c_str();
  }
};

class SynException : public exception
{
private:
  Token tkn;
  string expected;
  string message;

public:
  SynException(const Token &_tkn, const string &_expected)
      : tkn(_tkn), expected(_expected)
  {
    stringstream error_desc;
    error_desc << "(SYNTATIC ERROR) in " << tkn.getPosition() << ": " << expected << " near " << tkn.getlexem() << " of type " << tkn.getType()<< endl;
    message = error_desc.str();
  }
  const char *what() const throw()
  {
    return message.c_str();
  }
};

#endif