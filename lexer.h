//
// Created by jerry on 9/7/26.
//

#ifndef PFORGE_LEXER_H
#define PFORGE_LEXER_H
#include <string.h>

#include "Token.h"

Token lexerNextToken(const char* source, int* line, int* pos);

inline TokenType matchKeyword(const char* word, int length) {
    Token tk;

    if (strncmp(word, "packet", length) == 0 && length ==6) {
        return tk.type = TOK_PACKET;
    }
    if (strncmp(word, "u8", length) == 0 && length == 2) {
        return tk.type = TOK_U8;
    }
    if (strncmp(word, "u16be", length) == 0 && length == 5) {
        return tk.type = TOK_U16BE;
    }
    if (strncmp(word, "u16le", length) == 0 && length == 5) {
        return tk.type = TOK_U16LE;
    }
    if (strncmp(word, "u32be", length) == 0 && length == 5) {
        return tk.type = TOK_U32BE;
    }
    if (strncmp(word, "u32be", length) == 0 && length == 5) {
        return tk.type = TOK_U32BE;
    }
    return tk;
}

#endif //PFORGE_LEXER_H


