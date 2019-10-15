#include <iostream>
#include "include/Token.h"


int main() {
	std::cout << "Hello, World!" << std::endl;
	LexemType fru = LexemType::chr;
	Token token('a');
	std::cout << token.value() << std::endl;
	std::cout << token.str() << std::endl;
	std::cout << enToStr(token.type()) << std::endl;
	//enToStr(fru);
	return 0;
}