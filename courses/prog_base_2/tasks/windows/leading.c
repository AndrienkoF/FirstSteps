#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leading.h"

struct leading_s{
    char name[20];
    char surname[20];
    int numRadioPrograms;
    int salary;
};

leading_t * leading_new() {
	leading_t * newLeading = malloc(sizeof(struct leading_s));
	strcpy(newLeading->name, "");
	strcpy(newLeading->surname, "");
	newLeading->numRadioPrograms = 0;
	newLeading->salary = 0;
	return newLeading;
}

void leading_free(leading_t * self) {
	free(self);
}

void leading_fill(leading_t * self, char * name, char * surname, int numRadioPrograms, int salary){
	strcpy(self->name, name);
	strcpy(self->surname, surname);
	self->numRadioPrograms = numRadioPrograms;
	self->salary = salary;
}

char * leading_getName(leading_t * self){
    return self->name;
}

char * leading_getSurname(leading_t * self){
    return self->surname;
}

int leading_getNumRadioPrograms(leading_t * self){
    return self->numRadioPrograms;
}

int leading_getSalary(leading_t * self){
    return self->salary;
}
