#ifndef PFORGE_PARSER_H
#define PFORGE_PARSER_H
#include "Token.h"

struct  Parser {
    Token* token;
    int curr_ind;
    int token_count;
};


#endif //PFORGE_PARSER_H
