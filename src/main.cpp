//
// Created by GabrGabr and 6rayWa1cher on 29.10.2019.
//

#include <iostream>
#include <fstream>
#include "include/Token.h"
#include "include/Scanner.h"


int main(int argc, char **argv) {
	std::ifstream ifile;
	std::string filename, input, output;
	bool printLexems = false;
	int i = 1;
	if (argc == 1 || (argc == 2 && std::string(argv[1]) == "-h") || (argc == 2 && std::string(argv[1]) == "--help")) {
		std::cout << "Usage:" << std::endl
				  << '\t' << "micric [options] [target]" << std::endl
				  << '\t' << "micric [options] -i [target]" << std::endl
				  << "Options:" << std::endl
				  << '\t' << "-i file" << '\t' << "Set target file" << std::endl
				  << '\t' << "-o file" << '\t' << "Set output file" << std::endl
				  << '\t' << "-lc" << '\t' << "Print lexems in console";
		return 1;
	}
	while (i < argc) {
		input = std::string(argv[i]);
		if (input == "-i") {
			if (argc <= i + 1) {
				std::cerr << "Empty -i" << std::endl;
				return 1;
			}
			filename = argv[i + 1];
			i += 2;
		} else if (input == "-o") {
			if (argc <= i + 1) {
				std::cerr << "Empty -o" << std::endl;
				return 1;
			}
			output = argv[i + 1];
			i += 2;
		} else if (input == "-lc") {
			printLexems = true;
			++i;
		} else {
			filename = input;
			++i;
		}
	}
	ifile.open(filename);
	Scanner scanner(ifile);
	if (!ifile) {
		std::cerr << "Failed to open input file" << std::endl;
		return 1;
	}
	std::cout << "Opened input: " << filename << std::endl;
	std::ofstream ofile;
	if (!printLexems) {
		if (output.empty()) {
			ofile.open(filename + ".o");
		} else {
			ofile.open(output);
		}
		if (ofile) {
			std::cout << "Opened output: " << (output.empty() ? filename + ".o" : output) << std::endl;
		}
		if (!ofile && !output.empty() && !printLexems) {
			std::cerr << "Failed to create output file" << std::endl;
			return 1;
		}
	}
	Token currentLexem;
	do {
		currentLexem = scanner.getNextToken();
		if (printLexems) {
			currentLexem.print(std::cout);
			std::cout << std::endl;
		}
		if (ofile) {
			currentLexem.print(ofile);
			ofile << std::endl;
		}
		if (currentLexem.type() == LexemType::error) {
			std::cerr << "Lexical analysis error: " << std::endl
					  << "Position " << scanner.getRowPos() << ':'
					  << scanner.getColPos() << ": " << currentLexem.str() << std::endl;
			return 2;
		}
	} while (!(currentLexem.type() == LexemType::error || currentLexem.type() == LexemType::eof));
	ifile.close();
	ofile.close();
}
