#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

#include "thread.h"
#include "mutex.h"
#include "func.h"

#define MAX 5

int main(){

    char * mas[MAX];
    mas[0] = "Pink";
	mas[1] = "Fill";
	mas[2] = "Good";
	mas[3] = "Test string 2";
	mas[4] = "Test";
/*
    mas[0] = "Test string 6";
	mas[1] = "Test string 7";
	mas[2] = "String";
	mas[3] = "Red";
	mas[4] = "Test string 4";
*/
    array_t * array = array_new(mas);
    array_print(mas);
    writer_t * writerOne = writer_new(array);
	reader_t * readerOne = reader_new(array);

    writer_free(writerOne);
	reader_free(readerOne);
    array_free(array);

    return 0;
}
