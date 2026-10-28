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
    TOK_MAC_LIT,       // de:ad:be:ef:00:01 → value.string
    TOK_IP_LIT,        // 192.168.1.1       → value.string

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
    TOK_DOT,          // :
    TOK_COLON,          // :

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

        // Used by: TOK_IDENT, TOK_STRING_LIT, TOK_MAC_LIT, TOK_IP_LIT,
        // TOK_ERROR, TOK_PACKET
        // Heap-allocated copy made by the lexer via strndup().
        char* string;

        // Reserved for parsed MAC/IP values; the lexer currently stores text.
        uint8_t mac[6];
        uint32_t ip;

    } value;

    // Source line where this token appeared.
    // Used for error messages: "Error on line 7: expected ';'"
    int line;

} Token;

typedef enum {
    VALUE_NONE,
    VALUE_NUMBER,
    VALUE_STRING,
    VALUE_MAC,
    VALUE_IP,
} TokenValueType;

typedef enum {
    TYPE_U8,
    TYPE_U16BE,
    TYPE_U16LE,
    TYPE_U32BE,
    TYPE_U32LE
} TokenFieldType;

// A field definition within a packet.
typedef struct {
    TokenFieldType type;
    char name[64];
    int array_size; // 0 if not an array (e.g., u8[6] -> 6)
    
    TokenValueType val_type;
    union {
        uint64_t int_val;
        uint8_t mac_val[6];
        uint8_t ip_val[4];
    } value;
} FieldDef;

// A packet definition, which contains multiple fields.
typedef struct {
    char packet_name[64];
    FieldDef fields[64];
    int field_count;
} PacketDef;

void token_free(Token* tok);

// Prints a human-readable description of the token.
void token_print(const Token* tok);

#endif