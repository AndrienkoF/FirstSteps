#ifndef LEADING_H_INCLUDED
#define LEADING_H_INCLUDED

#define MAX_LEADINGÛ 7

typedef struct leading_s leading_t;

leading_t * leading_new(void);
void leading_free(leading_t * leading);

void leading_fill(leading_t* leading, int id, char* name, char* surname, int salary, int year);

int leading_getId(leading_t* );
char* leading_getName(leading_t*);
char* leading_getSurname(leading_t*);
int leading_getSalary(leading_t* );
int leading_getYear(leading_t* leading);


char* leading_makeLeadingJSON(leading_t *leading);
void leading_print(leading_t *leading);
char* leading_getLeading(leading_t* leading);

#endif // LEADING_H_INCLUDED
