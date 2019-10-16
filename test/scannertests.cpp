//
// Created by Konstantin Grigoriev on 16.10.2019.
//

#include <gtest/gtest.h>
#include "../src/include/Token.h"
#include "../src/include/Scanner.h"

TEST(ScannerTests, EmptyFile) {
	std::istringstream iss("");
	Scanner scanner(iss);
	Token *token = scanner.getNextToken();
	token->print(std::cerr);
	ASSERT_EQ(LexemType::eof, token->type());
}

TEST(ScannerTests, InvalidCharacter) {
	std::istringstream iss("кот");
	Scanner scanner(iss);
	Token *token = scanner.getNextToken();
	token->print(std::cerr);
	ASSERT_EQ(LexemType::error, token->type());
}

TEST(ScannerTests, DigitTests) {
	std::istringstream iss("5");
	Scanner *scanner = new Scanner(iss);
	Token *token = scanner->getNextToken();
	token->print(std::cerr);
	ASSERT_EQ(LexemType::num, token->type());
	ASSERT_EQ(5, token->value());
	token = scanner->getNextToken();
	token->print(std::cerr);
	ASSERT_EQ(LexemType::eof, token->type());

	iss = std::istringstream("5;");
	scanner = new Scanner(iss);
	token = scanner->getNextToken();
	token->print(std::cerr);
	ASSERT_EQ(LexemType::num, token->type());
	ASSERT_EQ(5, token->value());
	token = scanner->getNextToken();
	token->print(std::cerr);
	ASSERT_EQ(LexemType::comma, token->type());
	token = scanner->getNextToken();
	token->print(std::cerr);
	ASSERT_EQ(LexemType::eof, token->type());
}