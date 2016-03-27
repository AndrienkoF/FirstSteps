#include "thread.h"

#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

typedef thread_t writer_t;
typedef thread_t reader_t;

typedef struct array_s array_t;

array_t * array_new(char * myMas[]);
void array_free(array_t * list);
void array_print(char * myMas[]);

writer_t * writer_new(array_t * list);
reader_t * reader_new(array_t * list);

void writer_free(writer_t * list);
void reader_free(reader_t * list);

void * writer(void *args);
void * reader(void *args);

#endif // FUNC_H_INCLUDED
