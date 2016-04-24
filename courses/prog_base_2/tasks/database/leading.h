#ifndef LEADING_H_INCLUDED
#define LEADING_H_INCLUDED

typedef struct leading_s leading_t;
typedef struct leadingList_s leadingList_t;

struct leading_s{
    int id;
    char name[20];
    char surname[20];
    char birthdate[20];
    int numRadioPrograms;
    int salary;
    float rating;
};

struct leadingList_s {
	leading_t ** list;
	int size;
};



leading_t * leading_new();
void leading_free(leading_t * newLeading);
leadingList_t * leadingList_new(int size);
void leadingList_free(leadingList_t * newLeadingList);
void leading_fillL(leading_t * newLeading, char * name, char * surname, char * birthdate, int numRadioPrograms, int salary, float rating);
void leading_print(leading_t * newLeading);
void leadingList_print(leadingList_t * newLeadingList);
#endif // LEADING_H_INCLUDED
