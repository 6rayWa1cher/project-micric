#include <iostream>
#include "include/coolnumber.h"
#include "include/Token.h"

int main() {
	std::cout << "Hello, World!" << std::endl;
	std::cout << getCoolNumber() << std::endl;
	LexemType fru = LexemType::chr;
	Token token(fru);
	Token token2(5);
	return 0;
}