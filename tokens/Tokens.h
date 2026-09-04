#ifndef TOKENS_H
#define TOKENS_H

#include "../common.h"
#include "TokenType.h"

typedef struct {
    TokenType type;

    union {

        uint64_t TO_HEX_LIT;
        uint64_t TO_DEC_LIT;

        char* TOK_IDENT;
        char* TOK_STRING_LIT;

        uint8_t TOK_MAC_LIT[6];
        uint32_t TOK_IP_LIT;

    } value;

    int line;
} Token;
#endif
