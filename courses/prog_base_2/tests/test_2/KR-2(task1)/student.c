#include "student.h"

student_t * student_new(){
    student_t * newStudent = malloc(sizeof(struct student_s));
	newStudent->name = "NoName";
	newStudent->group = "NoSurname";
	newStudent->variant = 0;
	return newStudent;
}

void student_free(student_t * newStudent) {
	free(newStudent);
}

void student_fill(student_t * newStudent, char * name, char * group, int variant) {
	newStudent->name = name;
	newStudent->group = group;
	newStudent->variant = variant;
}
