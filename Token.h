#ifndef PFORGE_TOKEN_H
#define PFORGE_TOKEN_H

#include <stdint.h>

// Every possible token type.
// Numeric values are assigned automatically by the compiler.
typedef enum {
    // Literals — these carry actual data in the union
    TOK_HEX_LIT,       // 0x0800  → value.number
    TOK_DEC_LIT,       // 255     → value.number
    TOK_STRING_LIT,    // "hello" → value.string  (heap allocated, must free)
    TOK_IDENT,         // foo     → value.string  (heap allocated, must free)
    TOK_MAC_LIT,       // de:ad:be:ef:00:01 → value.mac
    TOK_IP_LIT,        // 192.168.1.1       → value.ip

    // Type keywords — no data needed beyond the type field itself
    TOK_U8,
    TOK_U16BE,
    TOK_U16LE,
    TOK_U32BE,
    TOK_U32LE,
    TOK_STR,
    TOK_COMPUTED,

    // Structural keyword
    TOK_PACKET,

    // Punctuation — no data needed beyond the type field itself
    TOK_LBRACE,        // {
    TOK_RBRACE,        // }
    TOK_LBRACKET,      // [
    TOK_RBRACKET,      // ]
    TOK_EQUALS,        // =
    TOK_SEMICOLON,     // ;

    // Control
    TOK_ERROR,         // unrecognised character → value.string holds message
    TOK_EOF,
} TokenType;

// The token itself.
typedef struct {
    TokenType type;

    union {
        // Used by: TOK_HEX_LIT, TOK_DEC_LIT
        // Both hex and decimal literals become the same thing once parsed —
        // a plain number.
        uint64_t number;

        // Used by: TOK_IDENT, TOK_STRING_LIT, TOK_ERROR
        // Heap-allocated copy made by the lexer via strndup().
        char* string;

        // Used by: TOK_MAC_LIT
        // Six bytes stored directly — no heap allocation needed.
        uint8_t mac[6];

        // Used by: TOK_IP_LIT
        // Four octets packed big-endian into one uint32_t.
        // 192.168.1.1 → 0xC0A80101
        // This matches what encode_u32be() will expect later.
        uint32_t ip;

    } value;

    // Source line where this token appeared.
    // Used for error messages: "Error on line 7: expected ';'"
    int line;

} Token;

// Call this on any token when you are done with it.
// Frees value.string for TOK_IDENT, TOK_STRING_LIT, and TOK_ERROR.
// Safe to call on any token type — does nothing for types with no heap data.
void token_free(Token* tok);

// Prints a human-readable description of the token.
void token_print(TokenType type);

#endif