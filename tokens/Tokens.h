#ifndef TOKENS_H
#define TOKENS_H

#include "../common.h"
#include "TokenType.h"

typedef struct {
    TokenType type;

    union {
        uint64_t hex_lit;
        uint64_t dec_lit;

        char* ident;
        char* string_lit;

        uint8_t mac_lit[6];
        uint32_t ip_lit;
    } value;

    int line;
} Token;

typedef struct {
    int count;
    int capacity;
    uint8_t* code;
} chunk;

#endif
