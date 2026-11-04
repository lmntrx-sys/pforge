#ifndef PFORGE_PARSER_H
#define PFORGE_PARSER_H
#include "Token.h"

struct  Parser {
    Token* token;
    int curr_ind;
    int token_count;
};

static Token expect(struct Parser parser, TokenType expected_token);

#endif //PFORGE_PARSER_H
