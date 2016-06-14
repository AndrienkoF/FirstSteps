#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "leading.h"
#include "../JSON/cJSON.h"


struct leading_s{
    int id;
    char name[50];
    char surname[50];
    int salary;
    int year;
};

leading_t* leading_new(void){
    leading_t * leading = malloc(sizeof(struct leading_s));
    leading->id = -1;
    strcpy(leading->name, "NoName");
    strcpy(leading->surname, "NoSurname");
    leading->salary = 0;
    leading->year = 0;
    return leading;
}

void leading_free(leading_t * leading){
    free(leading);
}

int leading_getId(leading_t* leading){
    return leading->id;
}

char* leading_getName(leading_t* leading){
    return leading->name;
}

char* leading_getSurname(leading_t* leading){
    return leading->surname;
}

int leading_getSalary(leading_t* leading){
    return leading->salary;
}

int leading_getYear(leading_t* leading){
    return leading->year;
}

void leading_fill(leading_t* leading, int id, char* name, char* surname, int salary, int year){
    leading->id = id;

    strcpy(leading->name, name);
    strcpy(leading->surname, surname);

    leading->salary = salary;
    leading->year = year;
}

char* leading_makeLeadingJSON(leading_t *leading){
    if(leading == NULL)
        return NULL;

    char* inJsn = NULL;

    cJSON* leadingJsn = cJSON_CreateObject();

    cJSON_AddItemToObject(leadingJsn, "Id", cJSON_CreateNumber(leading->id));
    cJSON_AddItemToObject(leadingJsn, "Name", cJSON_CreateString(leading->name));
    cJSON_AddItemToObject(leadingJsn, "Surname", cJSON_CreateString(leading->surname));
    cJSON_AddItemToObject(leadingJsn, "Salary", cJSON_CreateNumber(leading->salary));
    cJSON_AddItemToObject(leadingJsn, "Year", cJSON_CreateNumber(leading->year));

    inJsn = cJSON_Print(leadingJsn);
    cJSON_Delete(leadingJsn);
    return inJsn;
}

void leading_print(leading_t * leading){
    printf("Id: %i\nName: %s\nSurname: %s\nSalary: %i\nYear: %i\n\n----------------------\n\n",
        leading->id, leading->name, leading->surname,
        leading->salary, leading->year);
}

char* leading_getLeading(leading_t* leading){
    char one[500];
    sprintf(one,
            "     Id: %i\n"
            "   Name: %s\n"
            "Surname: %s\n"
            " Salary: %i\n"
            "   Year: %i\n\n",
            leading->id, leading->name, leading->surname,
            leading->salary, leading->year);
    return one;
}
