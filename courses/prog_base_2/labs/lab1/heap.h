#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

#include "memory.h"

typedef struct heap_s heap_t;
typedef enum heap_status{
    H_OK,
    H_FULL
} heap_status_t;

heap_t * new_heap(int sizeHeap, int id);
void heap_free(heap_t * newHeap);
int heap_size(heap_t * newHeap);
heap_status_t heap_status(heap_t * newHeap);
memory_t * heap_interactionMemory(heap_t * newHeap, int size);
void memory_free(memory_t * newMemory, heap_t * newHeap);


#endif // HEAP_H_INCLUDED
