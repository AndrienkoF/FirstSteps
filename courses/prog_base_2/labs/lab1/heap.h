#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

#include "memory.h"

typedef struct heap_s heap_t;
typedef enum heap_status{
    H_OK,
    H_FULL
} heap_status_t;

heap_t * heap_new(int sizeHeap, int id);
void heap_delete(heap_t * newHeap);
int heap_getSize(heap_t * newHeap);
heap_status_t heap_status(heap_t * newHeap);
memory_t * heap_interactionMemory(heap_t * newHeap, int size);


#endif // HEAP_H_INCLUDED
