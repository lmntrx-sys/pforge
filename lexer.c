#include "common.h"
#include "lexer.h"

Token lexerNextToken(const char* source, int* line, int* pos) {

    while (source[*pos] != '\0') {
        char c = source[*pos];

        if (c == ' ' || c == '\t' || c == '\r') {
            (*pos)++;
            continue;
        }

        if (c == '\n') {
            (*pos)++;
            (*line)++;
            continue;
        }
        break;
    }

    return next;
}
