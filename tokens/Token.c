#include "../common.h"
#include "Tokens.h"
#include <inttypes.h>


int retToken(Token tk) {

    uint64_t pr_token = tk.value.hex_lit;
    printf("0x%" PRIx64 "\n", pr_token);
    return 0;
}
int main(void) {
    Token tk;
    tk.type = TOK_HEX_LIT;
    tk.value.hex_lit = 0xDEADBEEF;
    tk.line = 1;
    retToken(tk);
    return 0;
}