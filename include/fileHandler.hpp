#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include "token.hpp"
#include "position.hpp"

using namespace std;
class FileHandler
{
protected:
  string filename;
  string ext_name;
  Position head;
  fstream content;

public:
  FileHandler();
  FileHandler(const string &);
  char getChar();
  void ungetChar();
  void nextLine();
  inline const Position getHead() { return head; };
  inline const string getExt_name() { return ext_name; };
  inline const string getFilename() { return filename; };
};

class TknHandler : FileHandler
{
private:
  vector<Token> token_list;
  Token *parser(const string &);

public:
  void submmit();
  TknHandler();
  TknHandler(const string &);
  void addToken(const Token &);
  vector<Token> load();
  Token *getToken();
};

#endif