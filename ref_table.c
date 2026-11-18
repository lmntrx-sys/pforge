#include "common.h"
#include "ref_table.h"
#include "Token.h"

Type_ref_entry type_table[] = {
    { .type_name = TOK_U8,    .byte_size = 1, .endian = ENDIAN_NONE,   .ctype = "uint8_t"  },
    { .type_name = TOK_U16BE, .byte_size = 2, .endian = ENDIAN_BIG,    .ctype = "uint16_t" },
    { .type_name = TOK_U16LE, .byte_size = 2, .endian = ENDIAN_LITTLE, .ctype = "uint16_t" },
    { .type_name = TOK_U32BE, .byte_size = 4, .endian = ENDIAN_BIG,    .ctype = "uint32_t" },
    { .type_name = TOK_U32LE, .byte_size = 4, .endian = ENDIAN_LITTLE, .ctype = "uint32_t" }
};


const int TYPE_TABLE_SIZE =sizeof(type_table) / sizeof(type_table[0]);