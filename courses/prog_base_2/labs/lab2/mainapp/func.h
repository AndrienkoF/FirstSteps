#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include "queue.h"

typedef int (*cmp_f)(queue_t * newQueue);
typedef void (*react_f)(queue_t * newQueue);

typedef struct dynamic_s {
    HANDLE hLib;
    cmp_f cmp;
    react_f react;
} dynamic_t;

dynamic_t * dynamic_init(const char * dllName);
void dynamic_clean(dynamic_t * dyn);

const char * userChoice();

#endif // MAIN_H_INCLUDED
