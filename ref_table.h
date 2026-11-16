//
// Created by jerry on 9/7/26.
//

#ifndef PFORGE_CHUNK_H
#define PFORGE_CHUNK_H

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
    const char* field_name;
} Type_ref_entry;


#endif //PFORGE_CHUNK_H
