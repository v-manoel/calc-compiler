#include "../include/lex.hpp"
#include "../include/fileHandler.hpp"
#include "../include/compilerException.hpp"
#include <iostream>
#include <string>
#include <cstring>

Lex::Lex() : reservedWords{
                 {"COS", TokenType::TK_COS},
                 {"SIN", TokenType::TK_SIN},
                 {"ROUND", TokenType::TK_ROUND},
                 {"ABS", TokenType::TK_ABS},
                 {"SQRT", TokenType::TK_SQRT},
                 {"TAN", TokenType::TK_TAN},
                 {"LOG", TokenType::TK_LOG},
                 {"PI", TokenType::TK_PI},
                 {"E", TokenType::TK_E}} {}

Lex::Lex(const string &in_file, const string &out_file) : Lex()
{
    fh_input = FileHandler(in_file);
    fh_output = out_file == "" ? TknHandler(in_file) : TknHandler(out_file);
}

Lex::~Lex()
{
    fh_output.submmit();
}

void Lex::scanner()
{
    string lexem;
    short state = 0;
    char currentChar = ' ';
    while (currentChar != EOF)
    {

        switch (state)
        {
        case 0:
            currentChar = getChar(lexem);

            switch (currentChar)
            {
            case '.':
                state = 2;

                break;

            case '+':
            case '-':
                state = 4;

                break;

            case '*':
            case '/':
            case '%':
                state = 5;

                break;

            case '^':
                state = 6;

                break;

            case ',':
                state = 7;

                break;

            case '(':
                state = 8;

                break;

            case ')':
                state = 9;

                break;

            case '\n':
                nextLine();
                lexem.pop_back();

                break;

            case EOF:
                state = currentChar;

                break;

            default:
                if (isSpace(currentChar))
                {
                    lexem.pop_back();
                    state = 0;
                }
                else if (isDigit(currentChar))
                {
                    state = 1;
                }
                else if (isLetter(currentChar))
                {
                    state = 10;
                }
                else
                {
                    throw LexException(fh_input.getHead(), lexem, "character valid");
                }

                break;
            }

            break;
        case 1:
            currentChar = getChar(lexem);

            if (currentChar == '.')
            {
                state = 3;
            }
            else if (!isDigit(currentChar))
            {
                // retorno do token TK_NUMBER...
                ungetChar(lexem);
                makeToken(TokenType::TK_NUMBER, lexem, fh_input.getHead());
                lexem.clear();
                state = 0;
            }

            break;
        case 2:
            currentChar = getChar(lexem);

            if (isDigit(currentChar))
            {
                state = 3;
            }
            else
            {
                throw LexException(fh_input.getHead(), lexem, "number");
            }

            break;
        case 3:
            currentChar = getChar(lexem);

            if (!isDigit(currentChar))
            {
                // retorno do token TK_NUMBER...
                ungetChar(lexem);
                makeToken(TokenType::TK_NUMBER, lexem, fh_input.getHead());
                lexem.clear();
                state = 0;
            }

            break;
        case 4:
            // retorno do token TK_OPERATOR_L1...
            makeToken(TokenType::TK_OPERATOR_L1, lexem, fh_input.getHead());
            lexem.clear();
            state = 0;

            break;
        case 5:
            // retorno do token TK_OPERATOR_L2...
            makeToken(TokenType::TK_OPERATOR_L2, lexem, fh_input.getHead());
            lexem.clear();
            state = 0;

            break;
        case 6:
            // retorno do token TK_OPERATOR_L3...
            makeToken(TokenType::TK_OPERATOR_L3, lexem, fh_input.getHead());
            lexem.clear();
            state = 0;

            break;
        case 7:
            // retorno do token TK_SEPARATOR...
            makeToken(TokenType::TK_SEPARATOR, lexem, fh_input.getHead());
            lexem.clear();
            state = 0;

            break;
        case 8:
            // retorno do token TK_BEG_DELIMITER...
            makeToken(TokenType::TK_BEG_DELIMITER, lexem, fh_input.getHead());
            lexem.clear();
            state = 0;

            break;
        case 9:
            // retorno do token TK_END_DELIMITER...
            makeToken(TokenType::TK_END_DELIMITER, lexem, fh_input.getHead());
            lexem.clear();
            state = 0;

            break;
        case 10:
            currentChar = getChar(lexem);

            if (!isLetter(currentChar))
            {
                ungetChar(lexem);
                if (isReservedWord(lexem))
                {
                    makeToken(getReservedWordType(lexem), lexem, fh_input.getHead());
                    lexem.clear();
                    state = 0;
                }
                else
                {
                    throw LexException(fh_input.getHead(), lexem, "a valid function");
                }
            }
            else if (lexem.size() > 5)
            {
                throw LexException(fh_input.getHead(), lexem, "a valid function");
            }

            break;
        }
    }
}

Token Lex::makeToken(const TokenType &_type, const string &_lexem, const Position &_position)
{
    Token tkn = Token(_type, _lexem, _position);
    fh_output.addToken(tkn);
    // cout << tkn; //print recognized tokens
    return tkn;
}

char Lex::getChar(string &lexem)
{
    lexem.push_back(fh_input.getChar());
    return lexem.back();
}

char Lex::ungetChar(string &lexem)
{
    fh_input.ungetChar();
    char res = lexem.back();
    lexem.pop_back();
    return res;
}

void Lex::nextLine()
{
    fh_input.nextLine();
}

bool Lex::isReservedWord(const string &lexem)
{
    string upper_lexem;
    for (auto c : lexem)
    {
        upper_lexem += toupper(c);
    }
    return (reservedWords.count(upper_lexem) > 0);
}

TokenType Lex::getReservedWordType(const string &lexem)
{
    string upper_lexem;
    for (auto c : lexem)
    {
        upper_lexem += toupper(c);
    }
    auto it = reservedWords.find(upper_lexem);

    if (it != reservedWords.end())
        return it->second;
    else
    {
        throw LexException(fh_input.getHead(), lexem, "a valid function");
    }
}