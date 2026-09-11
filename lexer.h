//
// Created by jerry on 9/7/26.
//

#ifndef PFORGE_LEXER_H
#define PFORGE_LEXER_H
#include "Token.h"

Token lexerNextToken(const char* source, int* pos, int* line);

#endif //PFORGE_LEXER_H


