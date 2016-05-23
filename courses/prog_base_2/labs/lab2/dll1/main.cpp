#include <stdio.h>
#include <stdlib.h>

#include "main.h"

int compare(queue_t * newQueue){
    if (queue_getSize(newQueue) > 10){
        printf("\nQueue size > 10\n");
        return 1;
    }
    return 0;
}

int reaction(queue_t * newQueue){
    int i, sum = 0;
    printf("\nProcessing...\n");
    for (i = 0; i < 5; i++){
        sum += queue_dequeue(newQueue);
    }
    printf("\nSum of the first 5 elements: %i\n\n", sum);
    return sum;
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
