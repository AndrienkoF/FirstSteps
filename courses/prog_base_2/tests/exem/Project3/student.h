#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

typedef struct student_s student_t;
typedef struct studentList_s studentList_t;

struct student_s{
    int id;
    char name[20];
    char surname[20];
    char fatherName[20];
    char birthdate[20];
    char hometown[20];
};

struct studentList_s {
	student_t ** list;
	int size;
};



student_t * student_new();
void student_free(student_t * newStudent);
studentList_t * studentList_new(int size);
void studentList_free(studentList_t * newStudentList);
void student_fillL(student_t * newStudent, char * name, char * surname, char * fatherName, char * birthdate, char * hometown);
void student_print(student_t * newStudent);
void studentList_print(studentList_t * newStudentList);
#endif // STUDENT_H_INCLUDED
