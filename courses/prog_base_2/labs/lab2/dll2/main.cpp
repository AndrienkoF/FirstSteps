#include <stdio.h>
#include <stdlib.h>

#include "main.h"

static int lib2_getsum(queue_t * newQueue){
    int size = queue_getSize(newQueue);
    int i, sum = 0, temp;
    for(i = 0; i < size; i++){
        temp = queue_dequeue(newQueue);
        sum += temp;
        queue_enqueue(newQueue, temp);
    }
    return sum;
}

int reaction(queue_t * newQueue){
    int sum = lib2_getsum(newQueue);
    printf("\nProcessing...\n");
    while(sum >= 50){
        queue_dequeue(newQueue);
        sum = lib2_getsum(newQueue);
    }
    printf("\nSum: %i (<50)\n\n", sum);
    return 0;
}

int compare(queue_t * newQueue){
    int sum = lib2_getsum(newQueue);
    if (sum > 100){
        printf("\nSum: %i (>100)\n", sum);
        return 1;
    }
    return 0;
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved){
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
