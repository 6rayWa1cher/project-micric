#ifndef PROJECT_MICRIC_TOKEN_H
#define PROJECT_MICRIC_TOKEN_H

#include <string>


enum class LexemType {
	num, chr, str, id, lpar, rpar, lbrace, rbrace, lbracket, rbracket,
	semicolon, comma, colon, opassign, opplus, opminus, opmult, opinc, opeq, opne, oplt,
	opgt, ople, opnot, opor, opand, kwint, kwchar, kwif, kwelse, kwswitch, kwcase, kwwhile,
	kwfor, kwreturn, kwin, kwout, eof, error
};

std::string enToStr(LexemType type);


class Token {

private:

	LexemType _type;
	int _value = 0;
	std::string _str;


public:

	Token(LexemType type) {
		_type = type;
	}

	Token(int value) {
		_type = LexemType::num;
		_value = value;
	}

	Token(LexemType type, const std::string &str) {
		_type = type;
		_str = str;
	}

	Token(char c) {
		_type = LexemType::chr;
		_value = int(c);
		std::string s(1, c);
		_str = s;
	}

	LexemType type();

	int value();

	std::string str();

	void setType(LexemType type);

	void setVal(int value);

	void setStr(std::string &str);

	std::string toString();

	void print(std::ostream &stream);
};


#endif