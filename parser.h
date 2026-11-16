#ifndef PFORGE_PARSER_H
#define PFORGE_PARSER_H
#include <stdlib.h>

#include "Token.h"

typedef struct  {
    Token* token;       /* token from lexer */
    int curr_ind;       /* current index of the stream */
    int token_count;    /* number of tokens */
} Parser;


#endif //PFORGE_PARSER_H
