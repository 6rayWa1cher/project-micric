#include "..\include\Token.h"
#include <string>
using namespace std;


LexemType Token::type() {
	return _type;
}

int Token::value() {
	return _value;
}

string Token::str() {
	return _str;
}

void Token::setType(LexemType type) {
	_type = type;
}

void Token::setVal(int value) {
	_value = value;
}

void Token::setStr(string str) {
	_str = str;
}

void Token::print(ostream& stream) {
	cout << "[" << "]" << endl;
}
