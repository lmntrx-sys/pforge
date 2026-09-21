//
// Created by jerry on 9/7/26.
//

#ifndef PFORGE_LEXER_H
#define PFORGE_LEXER_H
#include <string.h>

#include "Token.h"

Token lexerNextToken(const char* source, int* line, int* pos);

TokenType matchKeyword(const char* word, int length);

#endif //PFORGE_LEXER_H


