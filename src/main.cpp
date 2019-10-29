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
    int i = 1;
    while (i < argc) {
        input = std::string(argv[i]);
        if (input == "-i") {
            if (argc <= i + 1) {
                std::cerr << "Empty -f" << std::endl;
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
        } else {
            filename = input;
            ++i;
        }
    }
    ifile.open(filename);
    Scanner scanner(ifile);
    if (!ifile) {
        std::cout << "Failed to open" << std::endl;
    }
    std::cout << "Opened input: " << filename << std::endl;
    std::ofstream ofile;
    ofile.open(output);
    if (ofile) {
        std::cout << "Opened output: " << output << std::endl;
    }
    Token currentLexem;
    do {
        currentLexem = scanner.getNextToken();
        currentLexem.print(!ofile ? std::cout : ofile);
    } while (!(currentLexem.type() == LexemType::error || currentLexem.type() == LexemType::eof));
    ifile.close();
    ofile.close();
}
