//
// Created by 6rayWa1cher on 29.10.2019.
//

#include "TestUtils.h"
#include <gtest/gtest.h>

void checkAllTokens(Scanner &scanner, const std::vector<Token> &vector) {
	Token token;
	for (Token t : vector) {
		token = scanner.getNextToken();
		token.print(std::cerr);
		ASSERT_EQ(t.type(), token.type());
		ASSERT_EQ(t.value(), token.value());
		ASSERT_EQ(t.str(), token.str());
	}
	token = scanner.getNextToken();
	token.print(std::cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

void checkFails(Scanner &scanner, std::string errorMessage) {
	Token token;
	do {
		token = scanner.getNextToken();
		token.print(std::cerr);
		if (token.type() == LexemType::error) {
			ASSERT_EQ(errorMessage, token.str());
			return;
		}
	} while (token.type() != LexemType::eof);
	FAIL();
}
