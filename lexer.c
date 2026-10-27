#include "lexer.h"
#include <ctype.h>
#include <stdbool.h>
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
    int length = 1;
    tok.value.string = NULL;

    while (isxdigit((unsigned char)source[*pos]) || source[*pos] == ':') {
        (*pos)++;
        length++;
    }

    if (length == 17) { // MAC address format: XX:XX:XX:XX:XX:XX
        tok.type = TOK_MAC_LIT;
        tok.value.string = strndup(source + start, (size_t)length);
        if (tok.value.string == NULL) {
            tok.type = TOK_ERROR;
            tok.line = *line;
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
    int length = 1;
    tok.value.string = NULL;

    while (isdigit((unsigned char)source[*pos]) || source[*pos] == '.') {
        (*pos)++;
        length++;
    }
    
    // Validate the IP address format (basic validation)
    int octets = 0;
    int octetLength = 0;
    unsigned int octetValue = 0;
    bool valid = true;

    // Check each character in the IP address substring
    for (int i = start; i < start + length; i++) {
        if (source[i] == '.') {
            if (octetLength == 0 || octetLength > 3 || octetValue > 255 || octets == 3) {
                valid = false;
                break;
            }
            octets++;
            octetLength = 0;
            octetValue = 0;
        } else {
            octetLength++;
            octetValue = octetValue * 10 + (unsigned int)(source[i] - '0'); // Convert char to int
            if (octetLength > 3 || octetValue > 255) {
                valid = false;
                break;
            }
        }
    }
    valid = valid && octets == 3 && octetLength > 0;

    if (valid) {
        tok.type = TOK_IP_LIT;
        tok.value.string = strndup(source + start, (size_t)length);
        if (tok.value.string == NULL) {
            tok.type = TOK_ERROR;
            tok.line = *line;
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

    // Check for MAC address pattern 
    if (isxdigit((unsigned char)c) && isxdigit((unsigned char)source[*pos]) && source[*pos+1] == ':') {
        return LexMAC(source, pos, line, tok);
    }
    
    // Handle numeric literals (hexadecimal and decimal)
    if (isdigit((unsigned char)c)){
        int lookahead = *pos - 1;
        bool hasDot = false;

        // Check if the number contains a dot, which indicates it might be an IP address
        while (isdigit((unsigned char)source[lookahead]) || source[lookahead] == '.') {
            if (source[lookahead] == '.') hasDot = true;
            lookahead++;
        }
        if (hasDot) {
            return LexIP(source, pos, line, tok);
        }

        const int start = *pos - 1;
        const bool isHex = source[start] == '0' && (source[start+1] == 'x' || source[start+1] == 'X');
        if (isHex && !isxdigit((unsigned char)source[start + 2])) {
            tok.line = *line;
            tok.type = TOK_ERROR;
            return tok;
        }
        char *endptr;
        // back up one since the curr is already consumed
        tok.value.number = strtoull(source + start, &endptr, 0);
        *pos = endptr - source; // advance pos to wherever stroull stopped
        tok.type = isHex ? TOK_HEX_LIT : TOK_DEC_LIT;
        tok.line = *line;
        return tok;
    }

    // Handle identifiers and keywords
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


    // Handle punctuation and operators
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
                };
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
