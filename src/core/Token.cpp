#include "../include/Token.h"
#include <iostream>
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



void Token::print(ostream& stream) {
	cout << "[" << "]" << endl;
}
