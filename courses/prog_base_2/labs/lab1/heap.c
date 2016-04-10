#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "heap.h"
#include "memory.h"

struct heap_s{
    heap_status_t status;
    int sizeHeap;
    int id;
};

struct memory_s{
    memory_status_t status;
    char * memory;
    int sizeMemory;
    int id;
};

heap_t * new_heap(int sizeHeap, int id){
    heap_t  * newHeap = malloc(sizeof(struct heap_s));
    newHeap->status = H_OK;
    newHeap->sizeHeap = sizeHeap;
    newHeap->id = id;
    return newHeap;
}

void heap_free(heap_t * newHeap){
    free(newHeap);
}

int heap_size(heap_t * newHeap){
    return newHeap->sizeHeap;
}

heap_status_t heap_status(heap_t * newHeap){
    return newHeap->status;
}

memory_t * heap_interactionMemory(heap_t * newHeap, int size){
    struct memory_s * newMemory = malloc(sizeof(struct memory_s));
    newMemory->memory = malloc(sizeof(char) * newHeap->sizeHeap);
    newMemory->memory = "";
    newMemory->id = newHeap->id;
    newMemory->status = M_EMPTY;
    newHeap->status = H_OK;
    if (size > newHeap->sizeHeap){
        newMemory->sizeMemory = 0;
        newHeap->status = H_FULL;
        return newMemory;
    }
    newMemory->sizeMemory = size;
    newHeap->sizeHeap = newHeap->sizeHeap - size;
    return newMemory;
}

void memory_free(memory_t * newMemory, heap_t * newHeap){
    newHeap->sizeHeap = newHeap->sizeHeap + newMemory->sizeMemory;
    free(newMemory->memory);
    free(newMemory);
}
