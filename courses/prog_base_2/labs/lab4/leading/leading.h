#ifndef LEADING_H_INCLUDED
#define LEADING_H_INCLUDED

#define MAX_LEADINGS 7

typedef struct leading_s leading_t;

leading_t * leading_new(void);
void leading_free(leading_t * leading);

void leading_fill(leading_t * leading, int id, char* name, char* surname, char* birthdate, int exp, double rating);

int leading_getId(leading_t* );
char* leading_getName(leading_t*);
char* leading_getSurname(leading_t*);
char* leading_getBirthdate(leading_t*);
int leading_getExp(leading_t*);
double leading_getRate(leading_t*);

int leading_leadingsCount(leading_t** leading);

char* leading_makeLeadingJSON(leading_t *leading);
void leading_print(leading_t *leading);

#endif // LEADING_H_INCLUDED
