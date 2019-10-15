#include <map>
#ifndef MINI_CPP_COMPILER_SCANNER_H
#define MINI_CPP_COMPILER_SCANNER_H

map<char, LexemType> punctuation{ { '[', LexemType::lbracket }, { ']', LexemType::rbracket },{'(',LexemType::lpar },{')',LexemType::rpar},{'{',LexemType::lbrace},{'}',LexemType::rbrace},{';',LexemType::semicolon},{',',LexemType::comma}, {':',LexemType::colon} };map<string, LexemType> keywords{ { "return", LexemType::kwreturn },{"int",LexemType::kwint},
{"char",LexemType::kwchar},{"if",LexemType::kwif},{"else",LexemType::kwelse},{"switch",LexemType::kwswitch},
{"case",LexemType::kwcase},{"while",LexemType::kwwhile},{"for",LexemType::kwfor},{"in",LexemType::kwin},
{"out",LexemType::kwout} };

#endif
