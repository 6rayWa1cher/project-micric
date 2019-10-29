//
// Created by 6rayWa1cher and GabrGabr and Elikeid on 16.10.2019.
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

TEST(ScannerTests, MinusCharacterTest) {
	std::istringstream iss("-");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::opminus, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, MinusNumCharacterTest) {
	std::istringstream iss("-4");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(-4, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, MinusNum2CharacterTest) {
	std::istringstream iss("-10");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(-10, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, MinusNum3CharacterTest) {
	std::istringstream iss("-12");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(-12, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, MinusTwoNumCharacterTest) {
	std::istringstream iss("12 - 19");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(12, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::opminus, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(19, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}
// ???
//	TEST(ScannerTests, MinusTwoNumCharacterTest) {
//		std::istringstream iss("12-19");
//		Scanner scanner(iss);
//		Token token = scanner.getNextToken();
//		token.print(std::cerr);
//		ASSERT_EQ(LexemType::num, token.type());
//		ASSERT_EQ(12, token.value());
//		token = scanner.getNextToken();
//		token.print(std::cerr);
//		ASSERT_EQ(LexemType::opminus, token.type());
//		token = scanner.getNextToken();
//		token.print(std::cerr);
//		ASSERT_EQ(LexemType::num, token.type());
//		ASSERT_EQ(19, token.value());
//		token = scanner.getNextToken();
//		token.print(std::cerr);
//		ASSERT_EQ(LexemType::eof, token.type());
//	}
// ???

TEST(ScannerTests, MinusTwoNum2CharacterTest) {
	std::istringstream iss("12 + (-19)");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(12, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::opplus, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::lpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(-19, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::rpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
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

TEST(ScannerTests, IfCharacterTest) {
	std::istringstream iss("if");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::kwif, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, IfSignCharacterTest) {
	std::istringstream iss("if (a==10);");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::kwif, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::lpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("a", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::opeq, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(10, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::rpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, ForCharacterTest) {
	std::istringstream iss("for");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::kwfor, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, ForSignCharacterTest) {
	std::istringstream iss("for (i=0;i<10;i++)");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::kwfor, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::lpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("i", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::opassign, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(0, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("i", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::oplt, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(10, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("i", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::opinc, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::rpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, SwitchCharacterTest) {
	std::istringstream iss("switch");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::kwswitch, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, SwitchSignCharacterTest) {
	std::istringstream iss("switch (a*2);");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::kwswitch, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::lpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("a", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::opmult, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(2, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::rpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, OutCharacterTest) {
	std::istringstream iss("out");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::kwout, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, OutNumCharacterTest) {
	std::istringstream iss("out(42);");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::kwout, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::lpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(42, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);;
	ASSERT_EQ(LexemType::rpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, OutACharacterTest) {
	std::istringstream iss("out(res);");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::kwout, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::lpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("res", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::rpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, OutHWCharacterTest) {
	std::istringstream iss("out(\"Hello world!\");");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::kwout, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::lpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::str, token.type());
	ASSERT_EQ("Hello world!", token.str());
	scanner >> token;
	token.print(std::cerr);
	ASSERT_EQ(LexemType::rpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, InCharacterTest) {
	std::istringstream iss("in");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::kwin, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, WhileCharacterTest) {
	std::istringstream iss("while");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::kwwhile, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, WhileSignCharacterTest) {
	std::istringstream iss("while (a<=111);");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::kwwhile, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::lpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("a", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::ople, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(111, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::rpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, CaseCharacterTest) {
	std::istringstream iss("case");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::kwcase, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, ElseCharacterTest) {
	std::istringstream iss("else");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::kwelse, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, BracketCharacterTest) {
	std::istringstream iss("[]");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::lbracket, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::rbracket, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, ColonCharacterTest) {
	std::istringstream iss(":");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::colon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, CommaCharacterTest) {
	std::istringstream iss(",");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::comma, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, ParCharacterTest) {
	std::istringstream iss("()");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::lpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::rpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, BraceCharacterTest) {
	std::istringstream iss("{}");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::lbrace, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::rbrace, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, IntCharacterTest) {
	std::istringstream iss("int a;");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::kwint, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("a", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, MoreOneIntCharacterTest) {
	std::istringstream iss("int a=3,b=4,c=5;");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::kwint, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("a", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::opassign, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(3, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::comma, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("b", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::opassign, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(4, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::comma, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("c", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::opassign, token.type());
	token = scanner.getNextToken();
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

TEST(ScannerTests, CharCharacterTest) {
	std::istringstream iss("char b;");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::kwchar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("b", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, MoreOneCharCharacterTest) {
	std::istringstream iss("char a,b,c;");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::kwchar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("a", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::comma, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("b", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::comma, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("c", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, SignCharacterTest) {
	std::istringstream iss("=");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::opassign, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, CharsignCharacterTest) {
	std::istringstream iss("char b=17;");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::kwchar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("b", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::opassign, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(17, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, IntMasCharacterTest) {
	std::istringstream iss("int a[19];");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::kwint, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("a", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::lbracket, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(19, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::rbracket, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, CharMasCharacterTest) {
	std::istringstream iss("char buf[] = \"Hello world!\";");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::kwchar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("buf", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::lbracket, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::rbracket, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::opassign, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::str, token.type());
	ASSERT_EQ("Hello world!", token.str());
	scanner >> token;
	token.print(std::cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, GtPlusNotStatementTest) {
	std::istringstream iss("10+20>!a");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(10, token.value());
	scanner >> token;
	token.print(std::cerr);
	ASSERT_EQ(LexemType::opplus, token.type());
	scanner >> token;
	token.print(std::cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(20, token.value());
	scanner >> token;
	token.print(std::cerr);
	ASSERT_EQ(LexemType::opgt, token.type());
	scanner >> token;
	token.print(std::cerr);
	ASSERT_EQ(LexemType::opnot, token.type());
	scanner >> token;
	token.print(std::cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("a", token.str());
	scanner >> token;
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}
