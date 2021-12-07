#ifndef LEX_HPP
#define LEX_HPP

#include <cctype>
#include <map>

#include "token.hpp"
#include "fileHandler.hpp"
#include "compilerException.hpp"

class Lex
{

private:
    FileHandler fh_input;
    TknHandler fh_output;
    map<string, TokenType> reservedWords;

public:
    Lex();
    Lex(const string &, const string & = "");
    ~Lex();
    void scanner(); //return Token
    Token makeToken(const TokenType &, const string &, const Position &);

    inline bool isSpace(const char c)
    {
        return c == ' ' || c == '\t' || c == '\r';
    }

    inline bool isLetter(const char c)
    {
        return toupper(c) >= 'A' && toupper(c) <= 'Z';
    }

    inline bool isDigit(const char c)
    {
        return c >= '0' && c <= '9';
    }

    char getChar(string &lexem);
    char ungetChar(string &lexem);
    void nextLine();
    bool isReservedWord(const string &lexem);
    TokenType getReservedWordType(const string &lexem);
};

#endif
