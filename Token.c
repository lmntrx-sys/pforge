#include "common.h"
#include "Token.h"
#include <inttypes.h>
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

void token_print(const Token* t) {
    char type = t->type;
    char* value = t->value;

    printf("%c %c", type, *value);
}

int main () {
    return 0;

}