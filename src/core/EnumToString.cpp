#ifndef MINI_CPP_COMPILER_ENUMTOSTRING_H
#define MINI_CPP_COMPILER_ENUMTOSTRING_H

#include <string>
#include "..\include\Token.h"

void EnToStr(LexemType &type) {
	
	switch (type)
	{
	case LexemType::num: std::cout << "num";
	}
}