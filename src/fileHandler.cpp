#include "../include/position.hpp"
#include "../include/fileHandler.hpp"

using namespace std;
FileHandler::FileHandler() : head(0, 0) {}

FileHandler::FileHandler(const string &_filename) : FileHandler()
{
  filename = _filename;
  ext_name = ".fjrv";
  size_t ext_pos = _filename.find(ext_name);
  if (ext_pos == string::npos)
  {
    cout << "Error Extension File" << endl;
    exit(-1);
  }
  content.open(filename);
}

char FileHandler::getChar()
{
  head.column++;
  return content.get();
}

void FileHandler::ungetChar()
{
  head.column--;
  content.unget();
}

void FileHandler::nextLine()
{
  head.column = 0;
  head.line++;
}

TknHandler::TknHandler() : FileHandler() {}

TknHandler::TknHandler(const string &_filename) : FileHandler()
{
  filename = _filename;
  ext_name = ".tkn";

  const string ext_source = ".fjrv";
  size_t ext_pos = _filename.find(ext_source);
  if (ext_pos != string::npos)
  {
    filename.replace(ext_pos, 5, ext_name);
  }
  else if (_filename.find('.') == string::npos)
  {
    filename.append(ext_name);
  }
  else if (_filename.find(ext_name) == string::npos)
  {
    cout << "Error Extension File" << endl;
    exit(-1);
  }
}

vector<Token> TknHandler::load()
{
  content.open(filename, ios::in);
  if (content.is_open())
  {
    string str_tkn;
    while (getline(content, str_tkn))
    {
      Token *tkn = parser(str_tkn);
      if (tkn)
        addToken(*tkn);
    }
  }
  content.close();
  return token_list;
}

Token *TknHandler::parser(const string &line)
{
  size_t type_idx = line.find("type: ");
  size_t lexem_idx = line.find(" lexem: ");
  size_t pos_idx = line.find(" pos: ");
  size_t end_idx = line.find(" >");
  if (type_idx == string::npos || lexem_idx == string::npos || pos_idx == string::npos || end_idx == string::npos)
  {
    cout << "Parsing Error" << line << endl;
    exit(-1);
  }
  string type = line.substr(type_idx + 6, ((lexem_idx) - (type_idx + 6)));
  string lexem = line.substr(lexem_idx + 8, ((pos_idx) - (lexem_idx + 8)));
  string pos = line.substr(pos_idx + 6, ((end_idx) - (pos_idx + 6)));

  return new Token(Token::toTokenType(type), lexem, Position::toPosition(pos));
}

void TknHandler::submmit()
{
  content.open(filename, ios::app);
  if (content.good())
  {
    content.close();
    content.open(filename);
  }

  if (!content.is_open())
  {
    cout << "Error on submmit" << endl;
    exit(-1);
  }
  for (auto tkn : token_list)
  {
    content << tkn;
  }
  content.close();
}

void TknHandler::addToken(const Token &tkn)
{
  token_list.insert(token_list.end(), tkn);
}

Token *TknHandler::getToken()
{

  content.open(filename, ios::in);
  if (content.is_open())
  {
    string str_tkn;
    for (unsigned i = 0; i <= head.line && getline(content, str_tkn); i++)
      ;
    if (!content.eof())
    {
      Token *tkn = parser(str_tkn);
      if (!tkn)
      {
        cout << "Error reading file" << endl;
        exit(0);
      }
      nextLine();
      content.close();
      return tkn;
    }
    content.close();
  }
  return NULL;
}
