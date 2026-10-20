#include "lexer.h"
#include <ctype.h>
#include "Token.h"
#include <stdio.h>
#include <stdlib.h>

inline TokenType matchKeyword(const char* word, const int length) {
    if (length == 6 && strncmp(word, "packet", 6) == 0) return TOK_PACKET;
    if (length == 2 && strncmp(word, "u8", 2) == 0)     return TOK_U8;
    if (length == 5 && strncmp(word, "u16be", 5) == 0)  return TOK_U16BE;
    if (length == 5 && strncmp(word, "u16le", 5) == 0)  return TOK_U16LE;
    if (length == 5 && strncmp(word, "u32be", 5) == 0)  return TOK_U32BE;
    if (length == 5 && strncmp(word, "u32le", 5) == 0)  return TOK_U32LE; // Fixed duplicate u32be
    if (length == 6 && strncmp(word, "string", 6) == 0) return TOK_STR;

    return TOK_IDENT;
}

Token LexMAC(const char* source, int* pos, int* line, Token tok){
    
    int start = *pos - 1;
    int length = 0;

    while (isxdigit((unsigned char)source[*pos]) || source[*pos] == ':') {
        (*pos)++;
        length++;
    }

    if (length == 16) { // MAC address format: XX:XX:XX:XX:XX:XX
        tok.type = TOK_MAC_LIT;
        tok.value.string = strndup(source + start, (size_t)length);
        if (tok.value.string == NULL) {
            tok.type = TOK_ERROR;
            tok.value.string = strndup("Memory allocation failed for MAC address", 41);
            free(tok.value.string);
            return tok;
        }
        tok.line = *line;
        return tok;
    } else {
        // Not a valid MAC address, treat as an error or identifier
        tok.type = TOK_ERROR;
        tok.line = *line;
        return tok;
    }
}

Token LexIP(const char* source, int* pos, int* line, Token tok) {
    int start = *pos - 1;
    int length = 0;

    while (isdigit((unsigned char)source[*pos]) || source[*pos] == '.') {
        (*pos)++;
        length++;
    }

    if (length > 0 && length < 16) { // Basic validation for IP address format
        tok.type = TOK_IP_LIT;
        tok.value.string = strndup(source + start, (size_t)length);
        if (tok.value.string == NULL) {
            tok.type = TOK_ERROR;
            tok.value.string = strndup("Memory allocation failed for IP address", 40);
            free(tok.value.string);
            return tok;
        }
        tok.line = *line;
        return tok;
    } else {
        // Not a valid IP address, treat as an error or identifier
        tok.type = TOK_ERROR;
        tok.line = *line;
        return tok;
    }
}

Token lexerNextToken(const char* source, int* line, int* pos) {
    Token tok;
    // Skip whitespace and comments
    restart:
    while (source[*pos] != '\0') {
        const char c = source[*pos];
        if (c == ' ' || c == '\t' || c == '\r') { (*pos)++; continue; }
        if (c == '\n') { (*pos)++; (*line)++; continue; }
        break;
    }
    // Check for end of source
    if (source[*pos] == '\0') {
        tok.line= *line;
        tok.type = TOK_EOF;
        return tok;
    }

    const char c = source[*pos];
    (*pos)++;

    if (c == '-'){
        tok.line = *line;
        tok.type = TOK_ERROR;
        return tok;
    }

    if (isxdigit((unsigned char)c) && isxdigit((unsigned char)source[*pos]) && source[*pos + 1] == ':') {
        return LexMAC(source, pos, line, tok);
    }
    

    if (isdigit((unsigned char)c)){
        char *endptr;
        // back up one since the curr is already consumed
        tok.value.number = strtoull(source + *pos - 1, &endptr, 0);
        *pos = endptr - source; // advance pos to wherever stroull stopped
        tok.type = (source[*pos-1] == 'x' || source[*pos-1] == 'X') ? TOK_HEX_LIT : TOK_DEC_LIT;
        tok.line = *line;
        return tok;
    }

    if (isalpha((unsigned char)c) || c == '_') {
        int start = *pos - 1;

        while (isalnum((unsigned char)source[*pos]) || source[*pos] == '_') {
            (*pos)++;
        }
        int length = *pos - start;

        tok.type = matchKeyword(source+start, length);        

        if (tok.type == TOK_IDENT || tok.type == TOK_PACKET){
            tok.value.string = strndup(source+start, (size_t)length);
        }
        tok.line = *line;
        return tok;
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
                printf("Skipping comment: %c\n", source[*pos]);
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


