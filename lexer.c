#include "lexer.h"
#include <ctype.h>
#include "Token.h"

inline TokenType matchKeyword(const char* word, const int length) {
    if (length == 6 && strncmp(word, "packet", 6) == 0) return TOK_PACKET;
    if (length == 2 && strncmp(word, "u8", 2) == 0)     return TOK_U8;
    if (length == 5 && strncmp(word, "u16be", 5) == 0)  return TOK_U16BE;
    if (length == 5 && strncmp(word, "u16le", 5) == 0)  return TOK_U16LE;
    if (length == 5 && strncmp(word, "u32be", 5) == 0)  return TOK_U32BE;
    if (length == 5 && strncmp(word, "u32le", 5) == 0)  return TOK_U32LE; // Fixed duplicate u32be
    if (length == 6 && strncmp(word, "string", 6) == 0) return TOK_STR;

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


