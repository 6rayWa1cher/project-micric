//
// Created by 6rayWa1cher on 15.10.2019.
//

#include <gtest/gtest.h>
#include "../src/include/Token.h"

TEST(TokenTest, ConstructorEmpty) {
	std::ostringstream o;
	Token t1(LexemType::eof);
	t1.print(o);
	ASSERT_EQ("[eof]", o.str());
	ASSERT_EQ(LexemType::eof, t1.type());
	ASSERT_EQ(0, t1.value());
	ASSERT_EQ("", t1.str());
}

TEST(TokenTest, ConstructorString) {
	std::ostringstream o;
	Token t1(LexemType::id, "name");
	t1.print(o);
	ASSERT_EQ("[id, \"name\"]", o.str());
	ASSERT_EQ(LexemType::id, t1.type());
	ASSERT_EQ(0, t1.value());
	ASSERT_EQ("name", t1.str());
	o.str("");
	Token t2(LexemType::error, "символьная константа содержит более одного символа");
	t2.print(o);
	ASSERT_EQ("[error, \"символьная константа содержит более одного символа\"]", o.str());
	ASSERT_EQ(LexemType::error, t2.type());
	ASSERT_EQ(0, t2.value());
	ASSERT_EQ("символьная константа содержит более одного символа", t2.str());
}

TEST(TokenTest, ConstructorCharacter) {
	std::ostringstream o;
	Token t('a');
	t.print(o);
	ASSERT_EQ("[chr, 'a']", o.str());
	ASSERT_EQ(LexemType::chr, t.type());
    ASSERT_EQ('a', t.value());
	ASSERT_EQ("a", t.str());
}

TEST(TokenTest, ConstructorInteger) {
	std::ostringstream o;
	Token t(42);
	t.print(o);
	ASSERT_EQ("[num, 42]", o.str());
	ASSERT_EQ(LexemType::num, t.type());
	ASSERT_EQ(42, t.value());
	ASSERT_EQ("", t.str());
}
