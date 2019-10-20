//
// Created by 6rayWa1cher and GabrGabr on 16.10.2019.
//

#include <gtest/gtest.h>
#include "../src/include/Token.h"
#include "../src/include/Scanner.h"

TEST(ScannerTests, EmptyFile) {
	std::istringstream iss("");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, InvalidCharacter) {
	std::istringstream iss("кот");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::error, token.type());
}

TEST(ScannerTests, DigitTest) {
	std::istringstream iss("5");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(5, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}


TEST(ScannerTests, NumberTest) {
	std::istringstream iss("42");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(42, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, DigitCommaTest) {
	std::istringstream iss("5;");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(5, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, TwoNumbersTest) {
	std::istringstream iss("5;42");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(5, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(42, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, CharacterTest) {
	std::istringstream iss("'a'");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::chr, token.type());
	ASSERT_EQ("a", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, InvalidCharacterTest) {
	std::istringstream iss("'ab'");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::error, token.type());
}

TEST(ScannerTests, EmptyCharacterTest) {
	std::istringstream iss("''");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::error, token.type());
}

TEST(ScannerTests, TwoCharactersTest) {
	std::istringstream iss("'a';'b'");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::chr, token.type());
	ASSERT_EQ("a", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::chr, token.type());
	ASSERT_EQ("b", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, KeywordTest) {
	std::istringstream iss("return;");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::kwreturn, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, IdTest) {
	std::istringstream iss("myVar1");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("myVar1", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, KeywordAndIdTest) {
	std::istringstream iss("return myVar1;");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::kwreturn, token.type());
	scanner >> token;
	token.print(std::cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("myVar1", token.str());
	scanner >> token;
	token.print(std::cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	scanner >> token;
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, StringTest) {
	std::istringstream iss("\"Hello world!\"");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::str, token.type());
	ASSERT_EQ("Hello world!", token.str());
	scanner >> token;
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, StringUnexpectedEOFTest) {
	std::istringstream iss("\"Oh no, stream end");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::error, token.type());
}

TEST(ScannerTests, NotCharacterTest) {
	std::istringstream iss("!");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::opnot, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, NeCharacterTest) {
	std::istringstream iss("!=");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::opne, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, LtCharacterTest) {
	std::istringstream iss("<");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::oplt, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, LeCharacterTest) {
	std::istringstream iss("<=");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::ople, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, IncCharacterTest) {
	std::istringstream iss("+");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::opplus, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, NumIncCharacterTest) {
	std::istringstream iss("5++");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::num, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::opinc, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, OrCharacterTest) {
	std::istringstream iss("||");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::opor, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, InvalidOrCharacterTest) {
	std::istringstream iss("|'a'");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::error, token.type());
}

TEST(ScannerTests, AndCharacterTest) {
	std::istringstream iss("&&");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::opand, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, InvalidAndCharacterTest) {
	std::istringstream iss("&8");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::error, token.type());
}