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
	int _value;
	string _str;

public:

	Token(LexemType type) {
		setType(type);
	}

	Token(int value) {
		setType(LexemType::num);
		setVal(value);
	}

	Token(LexemType type, const string& str) {
		setType(type);
		setStr(str);
	}

	Token(char c) {
		setType(LexemType::chr);
		setVal(int(c));
		string s;
		s = "" + c;
		setStr(s);
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