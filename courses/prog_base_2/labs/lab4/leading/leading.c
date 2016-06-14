#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#include "leading.h"
#include "../JSON/cJSON.h"


struct leading_s{
    int id;
    char name[50];
    char surname[50];
    struct tm birthdate;
    int exp;
    double rating;
};

leading_t* leading_new(void){
    leading_t * leading = malloc(sizeof(struct leading_s));
    leading->id = -1;
    strcpy(leading->name, "");
    strcpy(leading->surname, "");
    memset(&leading->birthdate, 0, sizeof(leading->birthdate));
    leading->birthdate.tm_year = 0;
    leading->birthdate.tm_mday = 0;
    leading->birthdate.tm_mon = 0;
    leading->exp = 0;
    leading->rating = 0;
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

char* leading_getBirthdate(leading_t* leading){
    char buffer[300];
    sprintf(buffer, "%i-%i-%i", leading->birthdate.tm_year,
                                leading->birthdate.tm_mon,
                                leading->birthdate.tm_mday);
    return buffer;
}

int leading_getExp(leading_t* leading){
    return leading->exp;
}

double leading_getRate(leading_t* leading){
    return leading->rating;
}

void leading_fill(leading_t* leading, int id, char* name, char* surname, char* birthdate, int exp, double rating){
    char* str = NULL;
    char buffer[300];
    leading->id = id;

    strcpy(leading->name, name);
    strcpy(leading->surname, surname);
    leading->exp = exp;
    leading->rating = rating;

    strcpy(buffer, birthdate);

    str = strtok(buffer, "-");
    leading->birthdate.tm_year = atoi(str);
    str = strtok(NULL, "-");
    leading->birthdate.tm_mon = atoi(str);
    str = strtok(NULL, "\0");
    leading->birthdate.tm_mday = atoi(str);
}

char* leading_makeLeadingJSON(leading_t *leading){
    char* inJsn = NULL;
    char buffer[300];
    cJSON* leadingJsn = cJSON_CreateObject();

    cJSON_AddItemToObject(leadingJsn, "Id", cJSON_CreateNumber(leading->id));
    cJSON_AddItemToObject(leadingJsn, "Name", cJSON_CreateString(leading->name));
    cJSON_AddItemToObject(leadingJsn, "Surname", cJSON_CreateString(leading->surname));
    sprintf(buffer, "%i-%i-%i", leading->birthdate.tm_year,
                                leading->birthdate.tm_mon,
                                leading->birthdate.tm_mday);
    cJSON_AddItemToObject(leadingJsn, "Birth date", cJSON_CreateString(buffer));
    cJSON_AddItemToObject(leadingJsn, "Experience", cJSON_CreateNumber(leading->exp));
    cJSON_AddItemToObject(leadingJsn, "Rating", cJSON_CreateNumber(leading->rating));

    inJsn = cJSON_Print(leadingJsn);
    cJSON_Delete(leadingJsn);
    return inJsn;
}

void leading_print(leading_t * leading){
    printf("Id: %i\nName: %s\nSurname: %s\nBirth date: %i-%i-%i\nExperience: %i\nRating: %.2f\n\n----------------------\n\n",
        leading->id, leading->name, leading->surname, leading->birthdate.tm_year,
        leading->birthdate.tm_mon, leading->birthdate.tm_mday,
        leading->exp, leading->rating);
}

char* leading_getWorker(leading_t* leading)
{
    char one[500];
    sprintf(one,
            "        Id: %i\n"
            "      Name: %s\n"
            "   Surname: %s\n"
            "Birth date: %i-%i-%i\n"
            "Experience: %i\n"
            "    Rating: %.2f\n\n",
            leading->id, leading->name, leading->surname, leading->birthdate.tm_year,
            leading->birthdate.tm_mon, leading->birthdate.tm_mday,
            leading->exp, leading->rating);
    return one;
}

int leading_leadingsCount(leading_t** leadings){
    int count = 0;
    for(int i = 0; i<MAX_LEADINGS; i++){
        if(leading_getId(leadings[i]) >= 0){
            count++;
        }
    }
    return count;
}
