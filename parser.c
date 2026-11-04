#include "common.h"
#include "Token.h"
#include "parser.h"

#include <stdlib.h>

// current token
static Token peek(const struct Parser parser) {
    return parser.token[parser.curr_ind];
}

// TOK_EOF found
static bool is_at_end(struct Parser parser) {
    return parser.token->type == TOK_EOF;
}

// produce next token
static Token advance(struct Parser parser) {
    if (!is_at_end(parser)) {
        ++parser.curr_ind;
    }
    return parser.token[parser.curr_ind-1];
}

// lexical rules
static Token expect(struct Parser parser, TokenType expected_token) {
    const Token token = peek(parser);
    if (token.type == expected_token) {
        return advance(parser);
    }
    int line = token.line;
    fprintf(stderr, "Wrong token %d", line);
    exit(1);
}

void parse_field_definition(struct Parser parser) {
    // expect token identifier i.e u16, u8, u32
    expect(parser, TOK_IDENT);

    // optional array bounds e.g [8]
    int array_size = 1;
    if (peek(parser).type == TOK_LBRACKET){
        advance(parser);
        Token size_tok = expect(parser, TOK_DEC_LIT);
        array_size = string_to_int(size_tok.value);
        expect(parser, TOK_RBRACKET);
    }

    // e.g proto_addr_len
    Token field_name = expect(parser, TOK_IDENT);

    if (peek(parser).type == TOK_EQUALS){
        advance(parser);
        Token token_value = advance(parser);
        store_field_value(field_name, token_value);
    }

    expect(parser, TOK_SEMICOLON);
}


static Token parse_packet_definition(const struct Parser parser) {
    expect(parser, TOK_PACKET);

    // Expect packet name identifier
    Token name_token = expect(parser, TOK_IDENT);
    initialize_new_packet_ast(name_token.value);

    expect(parser, TOK_LBRACE); // {

    // Parse field until closing bracket
    while (peek(parser).type != TOK_RBRACE && (!is_at_end(parser))) {
        parse_field_definition(parser);

    }
    expect(parser, TOK_RBRACE); // }
}


void parse(struct Parser parser) {
    while (!is_at_end(parser)) {
        parse_packet_definition(parser);
    }
}

