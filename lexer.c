#include "lexer.h"
#include <ctype.h>
#include "Token.h"

inline TokenType matchKeyword(const char* word, const int length) {


    if (strncmp(word, "packet", length) == 0 && length == 6) {
        return TOK_PACKET;
    }
    if (strncmp(word, "u8", length) == 0 && length == 2) {
        return TOK_U8;
    }
    if (strncmp(word, "u16be", length) == 0 && length == 5) {
        return TOK_U16BE;
    }
    if (strncmp(word, "u16le", length) == 0 && length == 5) {
        return TOK_U16LE;
    }
    if (strncmp(word, "u32be", length) == 0 && length == 5) {
        return TOK_U32BE;
    }
    if (strncmp(word, "u32be", length) == 0 && length == 5) {
        return TOK_U32BE;
    }
    if (strncmp(word, "string", length) == 0 && length == 6) {
        return TOK_STR;
    }
    return TOK_ERROR;
}

Token lexerNextToken(const char* source, int* line, int* pos) {
    Token tok;

    restart:
    while (source[*pos] != '\0') {
        const char c = source[*pos];
        if (c == ' ' || c == '\t' || c == '\r') { (*pos)++; continue; }
        if (c == '\n') { (*pos)++; (*line)++; continue; }
        break;
    }

    if (source[*pos] == '\0') {
        tok.line= *line;
        tok.type = TOK_EOF;
        return tok;
    }

    const char c = source[*pos];
    (*pos)++;

    if (isalpha((unsigned char)c) || c == '_') {
        int start = *pos - 1;

        while (isalnum((unsigned char)source[*pos]) || source[*pos] == '_') {
            (*pos)++;
        }
        int length = *pos - start;

        tok.type = matchKeyword(source+start, length);

    }

    switch (c) {
        case '}':
            tok.line = *line;
            tok.type = TOK_RBRACE;
            break;

        case '{':
            tok.line = *line;
            tok.type = TOK_LBRACE;
            break;
        case '[':
            tok.line = *line;
            tok.type = TOK_LBRACKET;
            break;
        case ']':
            tok.line = *line;
            tok.type = TOK_RBRACKET;
            break;
        case ';':
            tok.line = *line;
            tok.type = TOK_SEMICOLON;
            break;
        case '=':
            tok.line = *line;
            tok.type = TOK_EQUALS;
            break;

        case '/':
            if (source[*pos] == '/') {
                while (source[*pos] != '\n' && source[*pos] != '\0'){
                    (*pos)++;
                }
                goto restart;
            } else {
                tok.type = TOK_ERROR;
                tok.line = *line;
                tok.value.string = strndup("unexpected character '/' ", 23);
                return tok;
            }
            break;

        default:
            tok.line = *line;
            tok.type = TOK_ERROR;
            break;
    }



    return tok;
}


