#include <iostream>
#include <fstream>
#include "include/Token.h"
#include "include/Scanner.h"


int main() {
	std::ifstream ifile;
	ifile.open("test.txt");
	Scanner scanner(ifile);
	if (!ifile) {
		std::cout << "Failed to open" << std::endl;
	}
	else {
		for (;;) {
			Token currentLexem = scanner.getNextToken();
			currentLexem.print(std::cout);
			if (currentLexem.type() == LexemType::error || currentLexem.type() == LexemType::eof) {
				break;
			}
		}
	}
}