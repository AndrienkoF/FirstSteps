#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "leading.h"

leading_t * leading_new() {
	leading_t * newLeading = malloc(sizeof(struct leading_s));
	return newLeading;
}

void leading_free(leading_t * newLeading) {
	free(newLeading);
}

leadingList_t * leadingList_new(int size) {
	if (size <= 0) {
		printf("Error, invalid index: %i\n", size);
		exit(1);
	}
	leadingList_t * newLeadingList = malloc(sizeof(struct leadingList_s));
	newLeadingList->list = calloc(size, sizeof(struct leading_s *));
	for (int i = 0; i < size; i++) {
		newLeadingList->list[i] = leading_new();
	}
	newLeadingList->size = 0;
	return newLeadingList;
}

void leadingList_free(leadingList_t * newLeadingList) {
	for (int i = 0; i < newLeadingList->size; i++) {
		free(newLeadingList->list[i]);
	}
	free(newLeadingList->list);
    free(newLeadingList);
}

void leading_fillL(leading_t * newLeading, char * name, char * surname, char * birthdate, int numRadioPrograms, int salary, float rating) {
	strcpy(newLeading->name, name);
	strcpy(newLeading->surname, surname);
	strcpy(newLeading->birthdate, birthdate);
	newLeading->numRadioPrograms = numRadioPrograms;
	newLeading->salary = salary;
	newLeading->rating = rating;

}

void leading_print(leading_t * newLeading) {
	printf("           Leading %i           \n", newLeading->id);
	printf("Name: %s\n", newLeading->name);
	printf("Surname: %s\n", newLeading->surname);
	printf("Birthdate: %s\n", newLeading->birthdate);
	printf("The number of radio programs: %i\n", newLeading->numRadioPrograms);
	printf("Salary: %i $\n", newLeading->salary);
	printf("Rating: %.1f\n", newLeading->rating);
	puts("\n\n");
}

void leadingList_print(leadingList_t * newLeadingList) {
	for (int i = 0; i < newLeadingList->size; i++) {
		leading_print(newLeadingList->list[i]);
	}
}
