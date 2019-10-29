//
// Created by 6rayWa1cher and GabrGabr and Elikeid on 16.10.2019.
//


#include <gtest/gtest.h>
#include "../src/include/Token.h"
#include "../src/include/Scanner.h"
#include "lib/TestUtils.h"


TEST(ScannerTests, EmptyFile) {
	std::istringstream iss("");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>());
}

TEST(ScannerTests, InvalidCharacter) {
	std::istringstream iss("кот");
	Scanner scanner(iss);
	checkFails(scanner, std::string("unknown symbol \xD0"));
}

TEST(ScannerTests, DigitTest) {
	std::istringstream iss("5");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(5)});
}


TEST(ScannerTests, NumberTest) {
	std::istringstream iss("42");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(42)});
}

TEST(ScannerTests, DigitCommaTest) {
	std::istringstream iss("5;");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(5), Token(LexemType::semicolon)});
}

TEST(ScannerTests, TwoNumbersTest) {
	std::istringstream iss("5;42");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(5), Token(LexemType::semicolon), Token(42)});
}

TEST(ScannerTests, CharacterTest) {
	std::istringstream iss("'a'");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token('a')});
}

TEST(ScannerTests, InvalidCharacterTest) {
	std::istringstream iss("'ab'");
	Scanner scanner(iss);
	checkFails(scanner, "invalid chr");
}

TEST(ScannerTests, EmptyCharacterTest) {
	std::istringstream iss("''");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(LexemType::error, "empty chr")});
}

TEST(ScannerTests, TwoCharactersTest) {
	std::istringstream iss("'a';'b'");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token('a'), Token(LexemType::semicolon), Token('b')});
}

TEST(ScannerTests, KeywordTest) {
	std::istringstream iss("return;");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(LexemType::kwreturn), Token(LexemType::semicolon)});
}

TEST(ScannerTests, IdTest) {
	std::istringstream iss("myVar1");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(LexemType::id, "myVar1")});
}

TEST(ScannerTests, KeywordAndIdTest) {
	std::istringstream iss("return myVar1;");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{
		Token(LexemType::kwreturn),
		Token(LexemType::id, "myVar1"),
		Token(LexemType::semicolon)
	});
}

TEST(ScannerTests, StringTest) {
	std::istringstream iss("\"Hello world!\"");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(LexemType::str, "Hello world!")});
}

TEST(ScannerTests, StringUnexpectedEOFTest) {
	std::istringstream iss("\"Oh no, stream end");
	Scanner scanner(iss);
	checkFails(scanner, "unexpected EOF");
}

TEST(ScannerTests, MinusCharacterTest) {
	std::istringstream iss("-");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(LexemType::opminus)});
}

TEST(ScannerTests, MinusNumCharacterTest) {
	std::istringstream iss("-4");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(-4)});
}

TEST(ScannerTests, MinusNum2CharacterTest) {
	std::istringstream iss("-10");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(-10)});
}

TEST(ScannerTests, MinusNum3CharacterTest) {
	std::istringstream iss("-12");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(-12)});
}

TEST(ScannerTests, MinusTwoNumCharacterTest) {
	std::istringstream iss("12 - 19");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(12), Token(LexemType::opminus), Token(19)});
}

TEST(ScannerTests, MinusTwoNum2CharacterTest) {
	std::istringstream iss("12 + (-19)");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{
		Token(12),
		Token(LexemType::opplus),
		Token(LexemType::lpar),
		Token(-19),
		Token(LexemType::rpar)
	});
}

TEST(ScannerTests, NotCharacterTest) {
	std::istringstream iss("!");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(LexemType::opnot)});
}

TEST(ScannerTests, NeCharacterTest) {
	std::istringstream iss("!=");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(LexemType::opne)});
}

TEST(ScannerTests, LtCharacterTest) {
	std::istringstream iss("<");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(LexemType::oplt)});
}

TEST(ScannerTests, LeCharacterTest) {
	std::istringstream iss("<=");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(LexemType::ople)});
}

TEST(ScannerTests, IncCharacterTest) {
	std::istringstream iss("+");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(LexemType::opplus)});
}

TEST(ScannerTests, NumIncCharacterTest) {
	std::istringstream iss("5++");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(5), Token(LexemType::opinc)});
}

TEST(ScannerTests, OrCharacterTest) {
	std::istringstream iss("||");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(LexemType::opor)});
}

TEST(ScannerTests, InvalidOrCharacterTest) {
	std::istringstream iss("|'a'");
	Scanner scanner(iss);
	checkFails(scanner, "unexpected statement: expected ||");
}

TEST(ScannerTests, AndCharacterTest) {
	std::istringstream iss("&&");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(LexemType::opand)});
}

TEST(ScannerTests, InvalidAndCharacterTest) {
	std::istringstream iss("&8");
	Scanner scanner(iss);
	checkFails(scanner, "unexpected statement: expected &&");
}

TEST(ScannerTests, IfCharacterTest) {
	std::istringstream iss("if");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(LexemType::kwif)});
}

TEST(ScannerTests, IfSignCharacterTest) {
	std::istringstream iss("if (a==10);");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{
		Token(LexemType::kwif),
		Token(LexemType::lpar),
		Token(LexemType::id, "a"),
		Token(LexemType::opeq),
		Token(10),
		Token(LexemType::rpar),
		Token(LexemType::semicolon)
	});
}

TEST(ScannerTests, ForCharacterTest) {
	std::istringstream iss("for");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(LexemType::kwfor)});
}

TEST(ScannerTests, ForSignCharacterTest) {
	std::istringstream iss("for (i=0;i<10;i++)");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{
		Token(LexemType::kwfor),
		Token(LexemType::lpar),
		Token(LexemType::id, "i"),
		Token(LexemType::opassign),
		Token(0),
		Token(LexemType::semicolon),
		Token(LexemType::id, "i"),
		Token(LexemType::oplt),
		Token(10),
		Token(LexemType::semicolon),
		Token(LexemType::id, "i"),
		Token(LexemType::opinc),
		Token(LexemType::rpar)
	});
}

TEST(ScannerTests, SwitchCharacterTest) {
	std::istringstream iss("switch");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(LexemType::kwswitch)});
}

TEST(ScannerTests, SwitchSignCharacterTest) {
	std::istringstream iss("switch (a*2);");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{
		Token(LexemType::kwswitch),
		Token(LexemType::lpar),
		Token(LexemType::id, "a"),
		Token(LexemType::opmult),
		Token(2),
		Token(LexemType::rpar),
		Token(LexemType::semicolon)
	});
}

TEST(ScannerTests, OutCharacterTest) {
	std::istringstream iss("out");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(LexemType::kwout)});
}

TEST(ScannerTests, OutNumCharacterTest) {
	std::istringstream iss("out(42);");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{
		Token(LexemType::kwout),
		Token(LexemType::lpar),
		Token(42),
		Token(LexemType::rpar),
		Token(LexemType::semicolon)
	});
}

TEST(ScannerTests, OutACharacterTest) {
	std::istringstream iss("out(res);");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{
		Token(LexemType::kwout),
		Token(LexemType::lpar),
		Token(LexemType::id, "res"),
		Token(LexemType::rpar),
		Token(LexemType::semicolon)
	});
}

TEST(ScannerTests, OutHWCharacterTest) {
	std::istringstream iss("out(\"Hello world!\");");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{
		Token(LexemType::kwout),
		Token(LexemType::lpar),
		Token(LexemType::str, "Hello world!"),
		Token(LexemType::rpar),
		Token(LexemType::semicolon)
	});
}

TEST(ScannerTests, InCharacterTest) {
	std::istringstream iss("in");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(LexemType::kwin)});
}

TEST(ScannerTests, WhileCharacterTest) {
	std::istringstream iss("while");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(LexemType::kwwhile)});
}

TEST(ScannerTests, WhileSignCharacterTest) {
	std::istringstream iss("while (a<=111);");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{
		Token(LexemType::kwwhile),
		Token(LexemType::lpar),
		Token(LexemType::id, "a"),
		Token(LexemType::ople),
		Token(111),
		Token(LexemType::rpar),
		Token(LexemType::semicolon)
	});
}

TEST(ScannerTests, CaseCharacterTest) {
	std::istringstream iss("case");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(LexemType::kwcase)});
}

TEST(ScannerTests, ElseCharacterTest) {
	std::istringstream iss("else");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(LexemType::kwelse)});
}

TEST(ScannerTests, BracketCharacterTest) {
	std::istringstream iss("[]");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{
		Token(LexemType::lbracket),
		Token(LexemType::rbracket)
	});
}

TEST(ScannerTests, ColonCharacterTest) {
	std::istringstream iss(":");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(LexemType::colon)});
}

TEST(ScannerTests, CommaCharacterTest) {
	std::istringstream iss(",");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(LexemType::comma)});
}

TEST(ScannerTests, ParCharacterTest) {
	std::istringstream iss("()");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(LexemType::lpar), Token(LexemType::rpar)});
}

TEST(ScannerTests, BraceCharacterTest) {
	std::istringstream iss("{}");
	Scanner scanner(iss);
	checkAllTokens(scanner, std::vector<Token>{Token(LexemType::lbrace), Token(LexemType::rbrace)});
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
