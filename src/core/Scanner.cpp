//
// Created by 6rayWa1cher and GabrGabr on 16.10.2019.
//
#include "../include/Scanner.h"
#include "../lib/CommonUtils.h"

Scanner::Scanner(std::istream &inputStream) : inputStream(inputStream) {

}

Scanner &operator>>(Scanner &scanner, Token &token) {
	token = scanner.getNextToken();
	return scanner;
}


Token Scanner::getNextToken() {
	if (stopped) {
		return stoppedAtToken;
	}
	while (true) {
		if (!stopAtCurrent || inputStream.eof()) {
			currentCharacter = inputStream.get();
			if (inputStream.eof() && currentState == 0) {
				stopped = true;
				stoppedAtToken = Token(LexemType::eof);
				return stoppedAtToken;
			} else if (inputStream.eof() &&
					   (currentState == 3 || currentState == 4 || currentState == 11 || currentState == 12)) {
				stopped = true;
				stoppedAtToken = Token(LexemType::error, "неожиданный конец потока");
				return stoppedAtToken;
			}
		}
		stopAtCurrent = false;
		if (currentState == 0) {
			if (CommonUtils::isDigit(currentCharacter)) {
				currentState = 1;
				integerValue = CommonUtils::charToInt(currentCharacter);
				continue;
			} else if (currentCharacter == '*') {
				return Token(LexemType::opmult);
			} else if (punctuation.find(currentCharacter) != punctuation.end()) {
				Token out(punctuation.find(currentCharacter)->second);
				return out;
			} else if (currentCharacter == ' ') {
				continue;
			} else if (currentCharacter == '\'') {
				currentState = 2;
				continue;
			} else if (currentCharacter == '!') {
				currentState = 7;
				continue;
			} else if (currentCharacter == '<') {
				currentState = 8;
				continue;
			} else if (currentCharacter == '=') {
				currentState = 9;
				continue;
			} else if (currentCharacter == '+') {
				currentState = 10;
				continue;
			} else if (currentCharacter == '|') {
				currentState = 11;
				continue;
			} else if (currentCharacter == '&') {
				currentState = 12;
				continue;
			} else if (currentCharacter == '"') {
				currentState = 4;
				continue;
			} else if (CommonUtils::isLetter(currentCharacter)) {
				currentState = 5;
				stringValue += currentCharacter;
				continue;
			} else if (currentCharacter == '-') {
				currentState = 6;
				continue;
			} 
		} else if (currentState == 1) {
			if (CommonUtils::isDigit(currentCharacter)) {
				if (negativeValue) {
					integerValue = integerValue * 10 - CommonUtils::charToInt(currentCharacter);
				}
				else {
					integerValue = integerValue * 10 + CommonUtils::charToInt(currentCharacter);
				}
				continue;
			} else {
				Token out(integerValue);
				currentState = 0;
				integerValue = 0;
				stopAtCurrent = true;
				return out;
			}
		} else if (currentState == 2) {
			if (currentCharacter == '\'') {
				stopped = true;
				return Token(LexemType::error, "пустой chr");
			} else {
				currentState = 3;
				characterValue = currentCharacter;
				continue;
			}
		} else if (currentState == 3) {
			if (currentCharacter == '\'') {
				Token out(characterValue);
				currentState = 0;
				return out;
			} else {
				stopped = true;
				stoppedAtToken = Token(LexemType::error, "более одного символа в chr");
				return stoppedAtToken;
			}
		} else if (currentState == 4) {
			if (currentCharacter == '"') {
				Token out(LexemType::str, stringValue);
				currentState = 0;
				stringValue = "";
				return out;
			} else {
				stringValue += currentCharacter;
				continue;
			}
		} else if (currentState == 5) {
			if (CommonUtils::isLetter(currentCharacter) || CommonUtils::isDigit(currentCharacter)) {
				stringValue += currentCharacter;
				continue;
			} else if (keywords.find(stringValue) != keywords.end()) {
				Token out(keywords.find(stringValue)->second);
				stringValue = "";
				currentState = 0;
				stopAtCurrent = true;
				return out;
			} else {
				Token out(LexemType::id, stringValue);
				//stringValue = "";
				currentState = 0;
				stopAtCurrent = true;
				return out;
			}
		} else if (currentState == 6) {
			if (CommonUtils::isDigit(currentCharacter)) {
				integerValue = (-1) * CommonUtils::charToInt(currentCharacter);
				currentState = 1;
				negativeValue = true;
				continue;
			} else {
				Token out(LexemType::opminus);
				currentState = 0;
				stopAtCurrent = true;
				return out;
			}
		} else if (currentState == 7) {
			if (currentCharacter == '=') {
				Token out(LexemType::opne);
				currentState = 0;
				return out;
			} else {
				Token out(LexemType::opnot);
				currentState = 0;
				stopAtCurrent = true;
				return out;
			}
		} else if (currentState == 8) {
			if (currentCharacter == '=') {
				Token out(LexemType::ople);
				currentState = 0;
				return out;
			} else {
				Token out(LexemType::oplt);
				currentState = 0;
				stopAtCurrent = true;
				return out;
			}
		} else if (currentState == 9) {
			if (currentCharacter == '=') {
				Token out(LexemType::opeq);
				currentState = 0;
				return out;
			} else {
				Token out(LexemType::opassign);
				currentState = 0;
				stopAtCurrent = true;
				return out;
			}
		} else if (currentState == 10) {
			if (currentCharacter == '+') {
				Token out(LexemType::opinc);
				currentState = 0;
				return out;
			} else {
				Token out(LexemType::opplus);
				currentState = 0;
				stopAtCurrent = true;
				return out;
			}
		} else if (currentState == 11) {
			if (currentCharacter == '|') {
				Token out(LexemType::opor);
				currentState = 0;
				return out;
			} else {
				stopped = true;
				stoppedAtToken = Token(LexemType::error, "неожиданное выражение: ожидается ||");
				return stoppedAtToken;
			}
		} else if (currentState == 12) {
			if (currentCharacter == '&') {
				Token out(LexemType::opand);
				currentState = 0;
				return out;
			} else {
				stopped = true;
				stoppedAtToken = Token(LexemType::error, "неожиданное выражение: ожидается &&");
				return stoppedAtToken;
			}
		}
		stopped = true;
		std::string text = "неопознанный символ ";
		text += currentCharacter;
		stoppedAtToken = Token(LexemType::error, text);
		return stoppedAtToken;
	}
}