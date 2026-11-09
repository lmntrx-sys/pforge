#include <stdlib.h>

#include "common.h"
#include "memory.h"

int* arena_alloc(Arena* arena, size_t size){
    if (arena->offset + size > arena->capacity) {
        /* Insufficient memory for allocation */
        size_t new_capacity =  arena->capacity * 2;
        unsigned char* new_buffer = realloc(arena->buffer, new_capacity);

        if (!new_buffer){
            /* Handle allocation failure */
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        arena->buffer = new_buffer;
        arena->capacity = new_capacity;

    }
    int* ptr = (int*)(arena->buffer + arena->offset);
    arena->offset += size;
    return ptr;

}

int* arena_init(Arena* arena, size_t initial_capacity) {
    arena->buffer = malloc(initial_capacity);
    if (!arena->buffer) {
        /* Handle allocation failure */
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    arena->offset = 0;
    arena->capacity = initial_capacity;
    return (int*)arena->buffer;
}