#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "main.h"

int main(){
    queue_t * newQueue = queue_new();

    const char * dllName = userChoice();
    dynamic_t * dll = dynamic_init(dllName);
    if (NULL == dll) {
        printf("Can't load dynamic!\n");
        return 1;
    }
    if (NULL == dll->cmp) {
        printf("Can't get compare function!\n");
        return 1;
    }
    if (NULL == dll->react) {
        printf("Can't get reaction function!\n");
        return 1;
    }
    printf("Dynamic loaded!");

    srand(time(NULL));

    while (1){
        queue_enqueue(newQueue, rand() % 100);
        queue_show(newQueue);
        if(dll->cmp(newQueue)==1){
            dll->react(newQueue);
            queue_show(newQueue);
            system("pause");
            continue;
        }
        queue_show(newQueue);
    }
    queue_free(newQueue);
    dynamic_clean(dll);
    return 0;
}

const char * userChoice() {
    int dllNum = 0;
    while (dllNum < 1 || dllNum > 2) {
        printf("Choose DLL to load:\n1. dll1\n2. dll2\n> ");
        scanf("%i", &dllNum);
        if (dllNum == 1) {
            return "dll1.dll";
        } else if (dllNum == 2) {
            return "dll2.dll";
        }
    }
    return NULL;
}

dynamic_t * dynamic_init(const char * dllName) {
    dynamic_t * dyn = malloc(sizeof(struct dynamic_s));
    dyn->hLib = LoadLibrary(dllName);
    dyn->cmp = NULL;
    dyn->react = NULL;
    if (NULL != dyn->hLib) {
        dyn->cmp = (cmp_f)GetProcAddress(dyn->hLib, "compare");
        dyn->react = (react_f)GetProcAddress(dyn->hLib, "reaction");
        return dyn;
    } else {
        return NULL;
    }
}

void dynamic_clean(dynamic_t * dyn) {
    FreeLibrary(dyn->hLib);
    free(dyn);
}

