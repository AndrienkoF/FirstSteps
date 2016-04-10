#ifndef DEDICATEDMEMORY_H_INCLUDED
#define DEDICATEDMEMORY_H_INCLUDED

typedef struct memory_s memory_t;
typedef enum memory_status{
    M_OK,
    M_FULL,
    M_EMPTY,
    M_ERROR
} memory_status_t;

void memory_check(memory_t * newMemory, char * memory);
memory_status_t memory_status(memory_t * newMemory);
char * memory_view(memory_t * newMemory);
int memory_Size(memory_t * newMemory);

#endif // DEDICATEDMEMORY_H_INCLUDED
