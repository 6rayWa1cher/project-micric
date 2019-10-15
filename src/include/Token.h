#ifndef MINI_CPP_COMPILER_TOKEN_H
#define MINI_CPP_COMPILER_TOKEN_H

#include <string>
using namespace std;


enum class LexemType {
	num, chr, str, id, lpar, rpar, lbrace, rbrace, lbracket, rbracket,
	semicolon, comma, colon, opassign, opplus, opminus, opmult, opinc, opeq, opne, oplt,
	opgt, ople, opnot, opor, opand, kwint, kwchar, kwif, kwelse, kwswitch, kwcase, kwwhile,
	kwfor, kwreturn, kwin, kwout, eof, error
};


class Token {

private:

	LexemType _type;
	int _value = 0;
	string _str;


public:

	Token(LexemType type) {
		_type = type;
	}

	Token(int value) {
		_type = LexemType::num;
		_value = value;
	}

	Token(LexemType type, const string& str) {
		_type = type;
		_str = str;
	}

	Token(char c) {
		_type = LexemType::chr;
		_value = int(c);
		string s;
		s = "" + c;
		_str = s;
	}

	LexemType type();
	int value();
	string str();
	LexemType setType(LexemType type);
	void setVal(int value);
	void setStr(string str);
	void print(ostream& stream);
};


#endif