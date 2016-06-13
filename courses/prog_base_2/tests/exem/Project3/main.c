#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "database.h"

int main(){
	const int size = 4;
	studentList_t * newStudentList = studentList_new(size);
	db_t * newDb = db_new("database.db");
    student_t * newStudent = student_new();

	int countSize = db_getSize(newDb);
	printf("ALL STUDENT: %i\n\n", countSize);
    puts("-------------------------------------------------------------");

    db_readList(newDb, newStudentList);
	studentList_print(newStudentList);
	puts("-------------------------------------------------------------");

	puts("     CREATE NEW STUDENT     \n");
	/*
    student_fillL(newStudent , "dsgsdg", "sdgdsv","sdfsdf", "sdgsdg", "vhgfnhgh");
	//student_fillL(newStudent , name, surname, fatherName, birthday, hometown);
	db_create(newDb, newStudent);
	db_readList(newDb, newStudentList);
	studentList_print(newStudentList);
	puts("-------------------------------------------------------------");

	puts("     UPDATE STUDENT (BY INDEX 2)     \n");
	db_update(newDb, newStudent, 6);
	db_readList(newDb, newStudentList);
	studentList_print(newStudentList);
	puts("-------------------------------------------------------------");
*/
	student_free(newStudent);
	studentList_free(newStudentList);
	db_free(newDb);
    return 0;
}
