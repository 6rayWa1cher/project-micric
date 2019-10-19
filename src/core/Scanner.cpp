//
// Created by Konstantin Grigoriev on 16.10.2019.
//
#include "../include/Scanner.h"
#include "../lib/CommonUtils.h"

Scanner::Scanner(std::istream &inputStream) : inputStream(inputStream) {
	inputStream >> currentCharacter;
}

Token Scanner::getNextToken() {
	if (stopped) {
		return stoppedAtToken;
	}
	while (true) {
		if (currentCharacter == '\0' || currentCharacter == '\xFF') {
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
		if (currentState == 0) {
			if (CommonUtils::isDigit(currentCharacter)) {
				currentState = 1;
				integerValue = CommonUtils::charToInt(currentCharacter);
				currentCharacter = '\0';
				continue;
			} else if (currentCharacter == '*') {
				currentCharacter = '\0';
				return Token(LexemType::opmult);
			} else if (punctuation.find(currentCharacter) != punctuation.end()) {
				Token out(punctuation.find(currentCharacter)->second);
				currentCharacter = '\0';
				return out;
			} else if (currentCharacter == ' ') {
				currentCharacter = '\0';
				continue;
			} else if (currentCharacter == '\'') {
				currentState = 2;
				currentCharacter = '\0';
				continue;
			} else if (currentCharacter == '!') {
				currentState = 7;
				currentCharacter = '\0';
				continue;
			} else if (currentCharacter == '<') {
				currentState = 8;
				currentCharacter = '\0';
				continue;
			} else if (currentCharacter == '=') {
				currentState = 9;
				currentCharacter = '\0';
				continue;
			}
//			else if (CommonUtils::isLetter(currentCharacter)) {
//				currentState = 5;
//				stringValue += currentCharacter;
//				currentCharacter = '\0';
//				continue;
//			}
		} else if (currentState == 1) {
			if (CommonUtils::isDigit(currentCharacter)) {
				integerValue = integerValue * 10 + CommonUtils::charToInt(currentCharacter);
				currentCharacter = '\0';
				continue;
			} else {
				Token out(integerValue);
				currentState = 0;
				integerValue = 0;
				return out;
			}
		} else if (currentState == 2) {
			if (currentCharacter == '\'') {
				stopped = true;
				return Token(LexemType::error, "пустой chr");
			} else {
				currentState = 3;
				characterValue = currentCharacter;
				currentCharacter = '\0';
				continue;
			}
		} else if (currentState == 3) {
			if (currentCharacter == '\'') {
				Token out(characterValue);
				currentState = 0;
				characterValue = '\0';
				currentCharacter = '\0';
				return out;
			} else {
				stopped = true;
				stoppedAtToken = Token(LexemType::error, "более одного символа в chr");
				return stoppedAtToken;
			}
		} else if (currentState == 7) {
			if (currentCharacter == '=') {
				Token out(LexemType::opne);
				currentState = 0;
				currentCharacter = '\0';
				return out;
			} else {
				Token out(LexemType::opnot);
				currentState = 0;
				return out;
			}
		} else if (currentState == 8) {
			if (currentCharacter == '=') {
				Token out(LexemType::ople);
				currentState = 0;
				currentCharacter = '\0';
				return out;
			} else {
				Token out(LexemType::oplt);
				currentState = 0;
				return out;
			}
		} else if (currentState == 9) {
			if (currentCharacter == '=') {
				Token out(LexemType::opeq);
				currentState = 0;
				currentCharacter = '\0';
				return out;
			} else {
				Token out(LexemType::opassign);
				currentState = 0;
				return out;
			}
		}
		
		stopped = true;
		std::string text = "неопознанный символ ";
		text += currentCharacter;
		stoppedAtToken = Token(LexemType::error, text);
		return stoppedAtToken;
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

const Token &Scanner::getStoppedAtToken() const {
	return stoppedAtToken;
}
