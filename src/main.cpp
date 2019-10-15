#include <iostream>
#include "include/coolnumber.h"
#include "include/Token.h"
#include "include/EnumToString.h"

int main() {
	std::cout << "Hello, World!" << std::endl;
	std::cout << getCoolNumber() << std::endl;
	LexemType fru = LexemType::num;
	//Token token(fru);
	//Token token2(5);
	EnToStr(fru);
	return 0;
}