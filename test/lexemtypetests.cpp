//
// Created by 6rayWa1cher on 11.10.2019.
//

#include <gtest/gtest.h>
#include "../src/include/Token.h"

TEST(Lexem_type, To_String) {
	ASSERT_EQ("num", enToStr(LexemType::num));
	ASSERT_EQ("chr", enToStr(LexemType::chr));
	ASSERT_EQ("str", enToStr(LexemType::str));
	ASSERT_EQ("id", enToStr(LexemType::id));
	ASSERT_EQ("lpar", enToStr(LexemType::lpar));
	ASSERT_EQ("rpar", enToStr(LexemType::rpar));
	ASSERT_EQ("lbrace", enToStr(LexemType::lbrace));
	ASSERT_EQ("rbrace", enToStr(LexemType::rbrace));
	ASSERT_EQ("lbracket", enToStr(LexemType::lbracket));
	ASSERT_EQ("rbracket", enToStr(LexemType::rbracket));
	ASSERT_EQ("semicolon", enToStr(LexemType::semicolon));
	ASSERT_EQ("comma", enToStr(LexemType::comma));
	ASSERT_EQ("colon", enToStr(LexemType::colon));
	ASSERT_EQ("opassign", enToStr(LexemType::opassign));
	ASSERT_EQ("opplus", enToStr(LexemType::opplus));
	ASSERT_EQ("opminus", enToStr(LexemType::opminus));
	ASSERT_EQ("opmult", enToStr(LexemType::opmult));
	ASSERT_EQ("opinc", enToStr(LexemType::opinc));
	ASSERT_EQ("opeq", enToStr(LexemType::opeq));
	ASSERT_EQ("opne", enToStr(LexemType::opne));
	ASSERT_EQ("oplt", enToStr(LexemType::oplt));
	ASSERT_EQ("opgt", enToStr(LexemType::opgt));
	ASSERT_EQ("ople", enToStr(LexemType::ople));
	ASSERT_EQ("opnot", enToStr(LexemType::opnot));
	ASSERT_EQ("opor", enToStr(LexemType::opor));
	ASSERT_EQ("opand", enToStr(LexemType::opand));
	ASSERT_EQ("kwint", enToStr(LexemType::kwint));
	ASSERT_EQ("kwchar", enToStr(LexemType::kwchar));
	ASSERT_EQ("kwif", enToStr(LexemType::kwif));
	ASSERT_EQ("kwelse", enToStr(LexemType::kwelse));
	ASSERT_EQ("kwswitch", enToStr(LexemType::kwswitch));
	ASSERT_EQ("kwcase", enToStr(LexemType::kwcase));
	ASSERT_EQ("kwwhile", enToStr(LexemType::kwwhile));
	ASSERT_EQ("kwfor", enToStr(LexemType::kwfor));
	ASSERT_EQ("kwreturn", enToStr(LexemType::kwreturn));
	ASSERT_EQ("kwin", enToStr(LexemType::kwin));
	ASSERT_EQ("kwout", enToStr(LexemType::kwout));
	ASSERT_EQ("eof", enToStr(LexemType::eof));
	ASSERT_EQ("error", enToStr(LexemType::error));
}