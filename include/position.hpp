#ifndef POSITION_HPP
#define POSITION_HPP

#include <iostream>
#include <string>

using namespace std;
struct Position
{
  unsigned long line;
  unsigned long column;

  Position(const unsigned long _line, const unsigned long _column) : line(_line), column(_column) {}
  inline friend ostream &operator<<(ostream &os, const Position &pos)
  {
    os << "line: " << pos.line << " col: " << pos.column;
    return os;
  }
  static Position toPosition(const string &txt)
  {
    size_t line_idx = txt.find("line: ");
    size_t col_idx = txt.find(" col: ");
    if (line_idx == string::npos || col_idx == string::npos)
    {
      cout << "Casting Error" << txt << endl;
      exit(-1);
    }
    string line = txt.substr(line_idx + 6, ((col_idx) - (col_idx + 6)));
    string col = txt.substr(col_idx + 6);
    return Position(stoi(line), stoi(col));
  }
};

#endif