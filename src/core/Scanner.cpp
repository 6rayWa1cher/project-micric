#include "../include/Scanner.h"
#include "../lib/CommonUtils.h"

Scanner::Scanner(std::istream &inputStream) : inputStream(inputStream) {
	inputStream >> currentCharacter;
}

Token *Scanner::getNextToken() {
	if (stopped) {
		return new Token(LexemType::eof);
	}
	while (true) {
		if (currentCharacter == '\0') {
			inputStream >> currentCharacter;
			if (currentCharacter == '\0' && inputStream.eof() && currentState == 0) {
				stopped = true;
				return new Token(LexemType::eof);
			} else if (currentCharacter == '\0' && inputStream.eof() &&
					   (currentState == 3 || currentState == 4 || currentState == 11 || currentState == 12)) {
				stopped = true;
				return new Token(LexemType::error, "неожиданный конец потока");
			}
		}
		if (currentState == 0) {
			if (CommonUtils::isDigit(currentCharacter)) {
				currentState = 1;
				integerValue = CommonUtils::charToInt(currentCharacter);
				currentCharacter = '\0';
				continue;
			} else if (currentCharacter == '*') {
				currentCharacter = '\0';
				return new Token(LexemType::opmult);
			} else if (punctuation.find(currentCharacter) != punctuation.end()) {
				currentCharacter = '\0';
				return new Token(punctuation.find(currentCharacter)->second);
			}
		} else if (currentState == 1) {
			if (CommonUtils::isDigit(currentCharacter)) {
				integerValue = integerValue * 10 + CommonUtils::charToInt(currentCharacter);
				currentCharacter = '\0';
				continue;
			} else {
				Token *out = new Token(integerValue);
				currentState = 0;
				integerValue = 0;
				return out;
			}
		}
		stopped = true;
		std::string text = "неопознанный символ ";
		text += currentCharacter;
		return new Token(LexemType::error, text);
	}
}

int Scanner::getIntegerValue() const {
	return integerValue;
}

char Scanner::getCharacterValue() const {
	return characterValue;
}

const std::string &Scanner::getStringValue() const {
	return stringValue;
}

int Scanner::getCurrentState() const {
	return currentState;
}

char Scanner::getCurrentCharacter() const {
	return currentCharacter;
}
