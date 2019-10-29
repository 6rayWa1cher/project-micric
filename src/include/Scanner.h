//
// Created by 6rayWa1cher and Elikeid on 16.10.2019.
//
#ifndef PROJECT_MICRIC_SCANNER_H
#define PROJECT_MICRIC_SCANNER_H

#include <map>
#include <istream>
#include "Token.h"

static std::map<char, LexemType> punctuation{{'[', LexemType::lbracket},
											 {']', LexemType::rbracket},
											 {'(', LexemType::lpar},
											 {')', LexemType::rpar},
											 {'{', LexemType::lbrace},
											 {'}', LexemType::rbrace},
											 {';', LexemType::semicolon},
											 {',', LexemType::comma},
											 {':', LexemType::colon}};
static std::map<std::string, LexemType> keywords{{"return", LexemType::kwreturn},
												 {"int",    LexemType::kwint},
												 {"char",   LexemType::kwchar},
												 {"if",     LexemType::kwif},
												 {"else",   LexemType::kwelse},
												 {"switch", LexemType::kwswitch},
												 {"case",   LexemType::kwcase},
												 {"while",  LexemType::kwwhile},
												 {"for",    LexemType::kwfor},
												 {"in",     LexemType::kwin},
												 {"out",    LexemType::kwout}};

class Scanner {
private:
	int integerValue = 0;
	char characterValue = '\0';
	std::string stringValue = "";
	int currentState = 0;
	char currentCharacter = '\0';
	bool stopped = false;
	bool stopAtCurrent = false;
	bool negativeValue = false;
    int colPos = 1;
    int rowPos = 1;
	Token stoppedAtToken = Token(LexemType::eof);
	std::istream &inputStream;
public:
	Scanner(std::istream &inputStream);

    int getColPos() const;

    int getRowPos() const;

    Token getNextToken();
};

Scanner &operator>>(Scanner &scanner, Token &token);
#endif
