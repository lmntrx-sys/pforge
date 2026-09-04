#pragma once

// This file gives a view of the tokens that will describe our language

typedef  enum {
    TOK_HEX_LIT,     // 0X8000
    TOK_DEC_LIT,     // 255
    TOK_STRING_LIT,  // "hello"
    TOK_MAC_LIT,     // de:ad:be:ef:00:01
    TOK_IP_LIT,      // 192.168.1.10

    // type keywords
    TOK_U8,
    TOK_U16BE,
    TOK_U16LE,
    TOK_U32BE,
    TOK_U32LE,
    TOK_STR,
    TOK_COMPUTED,

    // structural keywords
    TOK_PACKET,

    // punctuation
    TOK_LBRACE,        // {
    TOK_RBRACE,        // }
    TOK_LBRACKET,      // [
    TOK_RBRACKET,      // ]
    TOK_EQUALS,        // =
    TOK_SEMICOLON,     // ;

    // identifier (field names, packet names)
    TOK_IDENT,

    // special
    TOK_EOF,
    TOK_ERROR,
} TokenType;
