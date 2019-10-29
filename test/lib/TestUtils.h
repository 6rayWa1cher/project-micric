//
// Created by 6rayWa1cher on 29.10.2019.
//

#ifndef PROJECT_MICRIC_TESTUTILS_H
#define PROJECT_MICRIC_TESTUTILS_H

#include <vector>
#include "../../src/include/Token.h"
#include "../../src/include/Scanner.h"

void checkAllTokens(Scanner &scanner, const std::vector<Token> &vector);

void checkFails(Scanner &scanner, std::string errorMessage);

#endif //PROJECT_MICRIC_TESTUTILS_H
