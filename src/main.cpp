#include <iostream>
#include "include/Token.h"


int main() {
	std::cout << "Hello, World!" << std::endl;
	LexemType fru = LexemType::chr;
	Token token('a');
	cout << token.value() << endl;
	cout << token.str() << endl;
	cout << enToStr(token.type()) << endl;
	//enToStr(fru);
	return 0;
}