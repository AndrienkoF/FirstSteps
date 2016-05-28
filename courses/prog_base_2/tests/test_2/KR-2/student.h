#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

typedef struct student_s student_t;

struct student_s{
    char * name;
    char * group;
    int variant;

};

student_t * student_new();
void student_free(student_t * newStudent);
void student_fill(student_t * newStudent, char * name, char * group, int variant);


#endif // STUDENT_H_INCLUDED
