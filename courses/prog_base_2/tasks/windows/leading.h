#ifndef LEADING_H_INCLUDED
#define LEADING_H_INCLUDED

typedef struct leading_s leading_t;

leading_t * leading_new(void);
void leading_free(leading_t * self);

void leading_fill(leading_t * self, char * name, char * surname, int numRadioPrograms, int salary);
char * leading_getName(leading_t * self);
char * leading_getSurname(leading_t * self);
int leading_getNumRadioPrograms(leading_t * self);
int leading_getSalary(leading_t * self);

#endif // LEADING_H_INCLUDED
