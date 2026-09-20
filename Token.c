#include "common.h"
#include "Token.h"
#include <stdlib.h>

#include "lexer.h"

void token_free(Token* t) {
    switch (t->type) {
        case TOK_IDENT:
        case TOK_STRING_LIT:
        case TOK_ERROR:
            free(t->value.string);
            t->value.string = NULL;
            break;
        default:
            break;
    }
}

//void token_print(const Token* tok) {
//  char type = tok->type;
//  char value = &tok->value;

//  printf("%c %c", type, value);
//}

