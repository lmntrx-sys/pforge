//
// Created by jerry on 9/7/26.
//

#ifndef PFORGE_CHUNK_H
#define PFORGE_CHUNK_H

#include "common.h"

typedef struct {
    int count;
    int capacity;
    uint8_t* code;
} Chunk;

void initChunk(Chunk *chunk);
void writeChunk(Chunk *chunk, uint8_t byte);
void freeChunk(Chunk *chunk);


#endif //PFORGE_CHUNK_H
