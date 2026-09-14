#include "common.h"
#include "Token.h"
#include <inttypes.h>
#include "lexer.h"


int retToken(Token tk) {

    uint64_t pr_token = tk.value.hex_lit;
    printf("0x%" PRIx64 "\n", pr_token);
    return 0;
}

int main(void) {
    int line = 1, pos = 0;
    Token t;
    do {
        const char* src = "packet Foo { }";
        t = lexerNextToken(src, &line, &pos);
        retToken(t);
    } while (t.type != TOK_EOF);
}