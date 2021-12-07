#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include "position.hpp"

using namespace std;

enum TokenType
{
	TK_NUMBER,
	TK_SEPARATOR,
	TK_END_DELIMITER,
	TK_BEG_DELIMITER,
	TK_OPERATOR_L1,
	TK_OPERATOR_L2,
	TK_OPERATOR_L3,
	TK_COS,
	TK_SIN,
	TK_ROUND,
	TK_ABS,
	TK_SQRT,
	TK_TAN,
	TK_LOG,
	TK_PI,
	TK_E,
	$
};

class Token
{

private:
	TokenType type;
	string lexem;
	Position position;

public:
	Token(const TokenType _type, const string _lexem, const Position _position) : type(_type), lexem(_lexem), position(_position) {}

	inline void setType(TokenType _type)
	{
		type = _type;
	}

	inline TokenType getType()
	{
		return type;
	}

	inline void setlexem(string _lexem)
	{
		lexem = _lexem;
	}

	inline string getlexem()
	{
		return lexem;
	}

	inline void setPosition(Position _position)
	{
		position = _position;
	}

	inline Position getPosition()
	{
		return position;
	}

	friend ostream &operator<<(ostream &, const Token &);

	static TokenType toTokenType(const string &);
	static string toString(const TokenType &);
};

#endif