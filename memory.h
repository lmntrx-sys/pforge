//
// Created by jerry on 9/7/26.
//

#ifndef PFORGE_MEMORY_H
#define PFORGE_MEMORY_H

#include "common.h"

#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)
#define GROW_ARRAY(type, pointer, oldCount, newCount) \
    (type*)reallocate(pointer, sizeof(type) * (oldCount), \
        sizeof(type) * (newCount))


void* reallocate(void *pointer, size_t oldSize, size_t newSize);
#endif //PFORGE_MEMORY_H
