#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "student.h"

student_t * student_new() {
	student_t * newStudent = malloc(sizeof(struct student_s));
	return newStudent;
}

void student_free(student_t * newStudent) {
	free(newStudent);
}

studentList_t * studentList_new(int size) {
	if (size <= 0) {
		printf("Error, invalid index: %i\n", size);
		exit(1);
	}
	studentList_t * newStudentList = malloc(sizeof(struct studentList_s));
	newStudentList->list = calloc(size, sizeof(struct student_s *));
	for (int i = 0; i < size; i++) {
		newStudentList->list[i] = student_new();
	}
	newStudentList->size = 0;
	return newStudentList;
}

void studentList_free(studentList_t * newStudentList) {
	for (int i = 0; i < newStudentList->size; i++) {
		free(newStudentList->list[i]);
	}
	free(newStudentList->list);
    free(newStudentList);
}

void student_fillL(student_t * newStudent, char * name, char * surname, char * fatherName, char * birthdate , char * hometown) {
	strcpy(newStudent->name, name);
	strcpy(newStudent->surname, surname);
	strcpy(newStudent->fatherName, fatherName);
	strcpy(newStudent->birthdate, birthdate);
	strcpy(newStudent->hometown, hometown);
}

void student_print(student_t * newStudent) {
	printf("           Student %i           \n", newStudent->id);
	printf("Name: %s\n", newStudent->name);
	printf("Surname: %s\n", newStudent->surname);
	printf("FatherName: %s\n", newStudent->fatherName);
	printf("Birthdate: %s\n", newStudent->birthdate);
	printf("Hometown: %s\n", newStudent->hometown);
	puts("\n\n");
}

void studentList_print(studentList_t * newStudentList) {
	for (int i = 0; i < newStudentList->size; i++) {
		student_print(newStudentList->list[i]);
	}
}
