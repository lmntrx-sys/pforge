
#ifndef PFORGE_CHUNK_H
#define PFORGE_CHUNK_H
#include "Token.h"

#include "common.h"

typedef enum {
    ENDIAN_NONE = 0,
    ENDIAN_BIG,
    ENDIAN_LITTLE

} Endianness;

typedef struct {
    TokenType type_name;
    unsigned int byte_size;
    Endianness endian;
    const char* ctype;
} Type_ref_entry;

extern Type_ref_entry type_table[];
extern const int TYPE_TABLE_SIZE;
#endif //PFORGE_CHUNK_H
