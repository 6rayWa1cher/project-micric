#include <iostream>
#include "include/coolnumber.h"
#include "include/Token.h"
#include "include/EnumToString.h"


int main() {
	std::cout << "Hello, World!" << std::endl;
	std::cout << getCoolNumber() << std::endl;
	LexemType fru = LexemType::chr;
	Token token('a');
	cout << token.value() << endl;
	cout << token.str() << endl;
	cout << enToStr(token.type()) << endl;
	//enToStr(fru);
	return 0;
}