//
// Created by 6rayWa1cher on 16.10.2019.
//

#include "CommonUtils.h"

bool CommonUtils::isDigit(char c) {
	return '0' <= c && c <= '9';
}

int CommonUtils::charToInt(char c) {
	return c - '0';
}
