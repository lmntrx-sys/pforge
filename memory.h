#ifndef PFORGE_MEMORY_H
#define PFORGE_MEMORY_H

#include "common.h"
/* Use an arena to allocate memory */

typedef struct {
    unsigned char* buffer;  /* large memory chunk */
    size_t offset;          /* current offset in chunk */
    size_t capacity;        /* size of chunk */
} Arena;

int* arena_init(Arena* arena, size_t initial_capacity);
int* arena_alloc(Arena* arena, size_t size);
#endif //PFORGE_MEMORY_H
