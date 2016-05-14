#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "heap.h"
#include "memory.h"

struct memory_s{
    memory_status_t status;
    char * memory;
    int sizeMemory;
    int id;
};

void memory_check(memory_t * newMemory, char * memory){
    newMemory->status = M_OK;
    if (strlen(memory) > newMemory->sizeMemory){
        newMemory->status = M_FULL;
    }
    if(strcmp(memory, "") == 0){
        newMemory->status = M_EMPTY;
    }
    strcpy(&(newMemory->memory), &memory);
}

memory_status_t memory_status(memory_t * newMemory){
    return newMemory->status;
}

char * memory_view(memory_t * newMemory){
    return newMemory->memory;
}

int memory_getSize(memory_t * newMemory){
    return newMemory->sizeMemory;
}

