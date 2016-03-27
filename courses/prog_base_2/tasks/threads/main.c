#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

#include "thread.h"
#include "mutex.h"

#define MAX 10

typedef struct array_s {
    char * mas[MAX];
    char * string;
    int ptrToMas;
	mutex_t * mutex;
}array_t;

void * writer(void * args){
    array_t * array = (array_t *)args;
    while(1){
        mutex_lock(array->mutex);
        Sleep(100);
		(array->ptrToMas)++;
		array->string = array->mas[array->ptrToMas];
		if ((array->ptrToMas) == MAX){
			(array->ptrToMas) = (array->ptrToMas) % MAX;
			puts("\nPanels term expired. Getting tested again after 2 sec...");
			Sleep(2000);
		}

		mutex_unlock(array->mutex);
        Sleep(100);
    }
    return NULL;
}

void * reader(void * args){
    array_t * array = (array_t *)args;
	int length;
	while (1) {
		mutex_lock(array->mutex);
		Sleep(100);

        (array->ptrToMas)++;
        length = strlen(array->mas[array->ptrToMas]);

		if (length <= 5){
            printf("%s\n", array->mas[array->ptrToMas]);
		}

		mutex_unlock(array->mutex);
        Sleep(100);
	}
    return NULL;
}

int main (void){
    array_t array;
    array.ptrToMas = -1;

    array.mas[0] = "Hello";
	array.mas[1] = "Hello string";
	array.mas[2] = "Test string 1";
	array.mas[3] = "Good";
	array.mas[4] = "Test string 2";
	array.mas[5] = "Test";
	array.mas[6] = "Test string 6";
	array.mas[7] = "Test string 7";
	array.mas[8] = "String";
	array.mas[9] = "Test3";
	array.mas[10]= "Test string 4";
	array.mutex = mutex_new();

    int i;
    for(i = 0; i <= MAX; i++){
        printf("%i) Input string: '%s'\n", i, array.mas[i]);
    }

	thread_t * writerOne = thread_create_args(writer, &array);
    Sleep(15);
	thread_t * readerOne = thread_create_args(reader, &array);
	thread_join(readerOne);

	thread_free(writer);
	thread_free(readerOne);

	mutex_free(array.mutex);

	puts("\nPress ANY KEY to exit the program...");

	return 0;

}
