#include "lexer.h"
#include "Token.h"

Token lexerNextToken(const char* source, int* line, int* pos) {
    Token tk;

    while (source[*pos] != '\0') {
        const char c = source[*pos];
        if (c == ' ' || c == '\t' || c == '\r') { (*pos)++; continue; }
        if (c == '\n') { (*pos)++; (*line)++; continue; }
        break;
    }

    if (source[*pos] == '\0') {
        tk.line= *line;
        tk.type = TOK_EOF;
        return tk;
    }

    const char c = source[*pos];
    (*pos)++;

    switch (c) {
        case '}':
            tk.line = *line;
            tk.type = TOK_RBRACE;
            break;

        case '{':
            tk.line = *line;
            tk.type = TOK_LBRACE;
            break;
        case '[':
            tk.line = *line;
            tk.type = TOK_LBRACKET;
            break;
        case ']':
            tk.line = *line;
            tk.type = TOK_RBRACKET;
            break;
        case ';':
            tk.line = *line;
            tk.type = TOK_SEMICOLON;
            break;
        case '=':
            tk.line = *line;
            tk.type = TOK_EQUALS;
            break;

        default:
            tk.line = *line;
            tk.type = TOK_ERROR;
            break;
    }
    return tk;
}

