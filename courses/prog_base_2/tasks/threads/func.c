#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

#include "thread.h"
#include "mutex.h"
#include "func.h"

#define MAX 5
#define MAX_STRING 30

typedef struct array_s {
    char * mas[MAX];
    char * string;
    int ptrToMas;
	mutex_t * mutex;
}array_t;


array_t * array_new(char * myMas[]) {
	array_t * myArray = malloc(sizeof(struct array_s));
	int i;
	for (i = 0; i < MAX; i++){
        myArray->mas[i] = myMas[i];
	}
	myArray->string = calloc(MAX_STRING, sizeof(char*));
	myArray->mutex = mutex_new();
	myArray->ptrToMas = 0;
	return myArray;
}

void array_free(array_t * list) {
	mutex_free(list->mutex);
	free(list);
}

void array_print(char * myMas[]){
    int i;
    for (i = 0; i < MAX; i++){
        printf("%i) String: '%s'\n", i, myMas[i]);
    }
}

writer_t * writer_new(array_t * list) {
	thread_t * writerOne = thread_create_args(writer, list);
	return writerOne;
}

reader_t * reader_new(array_t * list) {
	thread_t * readerOne = thread_create_args(reader, list);
	return readerOne;
}

void writer_free(writer_t * list) {
	thread_join(list);
	thread_free(list);
}

void reader_free(reader_t * list) {
	thread_join(list);
	thread_free(list);
}

void * writer(void * args){
    array_t * array = (array_t *)args;
    while(1){
        mutex_lock(array->mutex);
		array->string = array->mas[array->ptrToMas];
		if ((array->ptrToMas) == MAX ){
			(array->ptrToMas) = 0;
			puts("\nPanels term expired. Getting tested again after 2 sec...\n");
			Sleep(2000);
		}
		if (kbhit()) {
			break;
		}
        Sleep(100);
		mutex_unlock(array->mutex);
    }
    return NULL;
}

void * reader(void * args){
    array_t * array = (array_t *)args;
	int length;
	while (1) {
		mutex_lock(array->mutex);
        length = strlen(array->mas[array->ptrToMas]);
		if (length <= 5){
            printf("%s\n", array->mas[array->ptrToMas]);
		}
		if (kbhit()) {
			break;
		}
		array->ptrToMas = (array->ptrToMas) + 1;
		Sleep(100);
		mutex_unlock(array->mutex);
	}
    return NULL;
}
