#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>

#include <sqlite3.h>

#include "database.h"
#include "leading/leading.h"

struct db_s{
    sqlite3 * db;
};

static bool checkPersonalReq(db_t* base, char* salaryReq, int salaryVal, char* yearReq, int yearVal);
static void getLeading(sqlite3_stmt * stmt, leading_t * leading);

db_t * db_new(const char * dbFileName){
    db_t * base = malloc(sizeof(struct db_s));

    if(SQLITE_ERROR == sqlite3_open(dbFileName, &base->db)){
        printf("Can't open DataBase!\n");
        exit(1);
    }
    return base;
}

void db_free(db_t * base){
    sqlite3_close(base->db);
    free(base);
}

void db_insertLeading(db_t* base, leading_t* leading){
    int id = -1;
    sqlite3_stmt *stmt = NULL;

    char* sqlRequest = "INSERT INTO "
    "Leadings ('Name', 'Surname', 'Salary', 'Year') "
    "VALUES (?, ?, ?, ?);";

    if(SQLITE_OK != sqlite3_prepare_v2(base->db, sqlRequest, strlen(sqlRequest)+1, &stmt, NULL)){
        printf("Can't prepare Insert request!\n");
        exit(1);
    }

    char* name = leading_getName(leading);
    char* surname = leading_getSurname(leading);
    int salary = leading_getSalary(leading);
    int year = leading_getYear(leading);

    sqlite3_bind_text(stmt, 1, name, strlen(name), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, surname, strlen(surname), SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, salary);
    sqlite3_bind_int(stmt, 4, year);

    if(SQLITE_ERROR == sqlite3_step(stmt)){
        printf("Can't make step(insert)!\n");
        sqlite3_finalize(stmt);
    }else{
        id = sqlite3_last_insert_rowid(base->db);
        leading_fill(leading, id, name, surname, salary, year);
        leading_print(leading);
        sqlite3_finalize(stmt);
    }

}

leading_t * db_getLeadingById(db_t* base, unsigned int id){
    leading_t* toReturn = leading_new();
    sqlite3_stmt* stmt = NULL;

    char* sqlRequest =
    "SELECT * FROM Leadings WHERE Id = ?;";

    if(SQLITE_OK != sqlite3_prepare_v2(base->db, sqlRequest, strlen(sqlRequest)+1, &stmt, NULL)){
        printf("Can't prepare Get request!\n");
        exit(1);
    }

    sqlite3_bind_int(stmt, 1, id);

    if(SQLITE_ERROR == sqlite3_step(stmt)){
        printf("Can't make step(get)!\n");
        sqlite3_finalize(stmt);
    }

    getLeading(stmt, toReturn);
    sqlite3_finalize(stmt);

    return toReturn;
}

void db_deleteLeading(db_t* base, unsigned int id){
    sqlite3_stmt * stmt = NULL;

    char * sqlRequest =
        "DELETE FROM Leadings WHERE ID = ?;";

    if(SQLITE_OK != sqlite3_prepare_v2(base->db, sqlRequest, strlen(sqlRequest)+1, &stmt, NULL)){
        printf("Can't prepare Delete request!\n");
        exit(1);
    }

    sqlite3_bind_int(stmt, 1, id);

    if(SQLITE_ERROR == sqlite3_step(stmt)){
        printf("Can't make step(delete)!\n");
        sqlite3_finalize(stmt);
    }else{
        sqlite3_finalize(stmt);
    }
}

int db_countLeadings(db_t* base){
    sqlite3_stmt * stmt = NULL;
    int count = 0;

    const char * sqlRequest = "SELECT COUNT(*) FROM Leadings;";

    if(SQLITE_OK != sqlite3_prepare_v2(base->db, sqlRequest, strlen(sqlRequest)+1, &stmt, NULL)){
        printf("Can't prepare Count request!\n");
        exit(1);
    }

    if(SQLITE_ERROR == sqlite3_step(stmt)){
        printf("Can't take Count!\n");
        exit(1);
    }

    count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);

    return count;
}

char* db_personalTask(db_t* base, char* salaryReq, int salaryVal, char* yearReq, int yearVal, leading_t** leadings){
    if(!checkPersonalReq(base, salaryReq, salaryVal,yearReq, yearVal)){
        return "{\n\tThere is no Leadings with such parameters\n}";
    }

    sqlite3_stmt* stmt = NULL;
    int count = 0;
    char buffer[10000] = "";
    char sqlRequest[100]="";
    if(!strcmp(salaryReq, "salary_m") && !strcmp(yearReq, "year_m")){
        strcpy(sqlRequest, "SELECT * FROM Leadings WHERE Salary > ? AND Year > ?;");
    }
    else if(!strcmp(salaryReq, "salary_l") && !strcmp(yearReq, "year_l")){
        strcpy(sqlRequest, "SELECT * FROM Leadings WHERE Salary < ? AND Year < ?;");
    }
    else if(!strcmp(salaryReq, "salary_m") && !strcmp(yearReq, "year_l")){
        strcpy(sqlRequest, "SELECT * FROM Leadings WHERE Salary > ? AND Year < ?;");
    }
    else
        strcpy(sqlRequest, "SELECT * FROM Leadings WHERE Salary < ? AND Year > ?;");

    if(SQLITE_OK != sqlite3_prepare_v2(base->db, sqlRequest, strlen(sqlRequest)+1, &stmt, NULL)){
        printf("Can't prepare Personal request!\n");
        exit(1);
    }

    sqlite3_bind_int(stmt, 1, salaryVal);
    sqlite3_bind_int(stmt, 2, yearVal);

    while(true){
        int status = sqlite3_step(stmt);
        if(SQLITE_ERROR == status){
            printf("Can't select leading!\n");
            exit(1);
        }
        else if(SQLITE_DONE == status){
            break;
        }else{
            getLeading(stmt, leadings[count]);
            strcat(buffer, leading_makeLeadingJSON(leadings[count]));
            count++;
        }
    }
    sqlite3_finalize(stmt);
    return buffer;
}

static bool checkPersonalReq(db_t* base, char* salaryReq, int salaryVal, char* yearReq, int yearVal){
    sqlite3_stmt* stmt = NULL;
    char sqlRequest[100]="";
    if(!strcmp(salaryReq, "salary_m") && !strcmp(yearReq, "year_m")){
        strcpy(sqlRequest, "SELECT * FROM Leadings WHERE Salary > ? AND Year > ?;");
    }
    else if(!strcmp(salaryReq, "salary_l") && !strcmp(yearReq, "year_l")){
        strcpy(sqlRequest, "SELECT * FROM Leadings WHERE Salary < ? AND Year < ?;");
    }
    else if(!strcmp(salaryReq, "salary_m") && !strcmp(yearReq, "year_l")){
        strcpy(sqlRequest, "SELECT * FROM Leadings WHERE Salary > ? AND Year < ?;");
    }
    else
        strcpy(sqlRequest, "SELECT * FROM Leadings WHERE Salary < ? AND Year > ?;");

    if(SQLITE_OK != sqlite3_prepare_v2(base->db, sqlRequest, strlen(sqlRequest)+1, &stmt, NULL)){
        printf("Can't prepare Personal request!\n");
        exit(1);
    }

    sqlite3_bind_int(stmt, 1, salaryVal);
    sqlite3_bind_int(stmt, 2, yearVal);

    if(SQLITE_ERROR == sqlite3_step(stmt)){
        printf("Can't make step(CheckPersonalTask)!\n");
        exit(1);
    }

    int check = sqlite3_column_int(stmt, 0);

    sqlite3_finalize(stmt);

    if(check > 0)
        return true;
    else
        return false;
}

static void getLeading(sqlite3_stmt * stmt, leading_t * leading){
    int id = sqlite3_column_int(stmt, 0);
    char* name = sqlite3_column_text(stmt, 1);
    char* surname = sqlite3_column_text(stmt, 2);
    int salary = sqlite3_column_int(stmt, 3);
    int year = sqlite3_column_int(stmt, 4);

    leading_fill(leading, id, name, surname, salary, year);
}

bool db_checkId(db_t* base, unsigned int id){
    sqlite3_stmt* stmt = NULL;

    char* sqlRequest = "SELECT COUNT(*) FROM Leadings WHERE Id = ?;";

    if(SQLITE_OK != sqlite3_prepare_v2(base->db, sqlRequest, strlen(sqlRequest)+1, &stmt, NULL)){
        printf("Can't prepare CheckID request!\n");
        exit(1);
    }

    sqlite3_bind_int(stmt, 1, id);

    if(SQLITE_ERROR == sqlite3_step(stmt)){
        printf("Can't make step(CheckID)!\n");
        exit(1);
    }

    int check = sqlite3_column_int(stmt, 0);

    sqlite3_finalize(stmt);

    if(check == 1)
        return true;
    else
        return false;
}

void  db_fillLeadingArr(db_t* base, leading_t** leadings){
    int count = 0;

    sqlite3_stmt* stmt = NULL;

    char* sqlRequest = "SELECT * FROM Leadings;";

    if(SQLITE_OK != sqlite3_prepare_v2(base->db, sqlRequest, strlen(sqlRequest)+1, &stmt, NULL)){
        puts("Cant make prepare for leadings array");
        exit(1);
    }

    while(true){
        int status = sqlite3_step(stmt);
        if(SQLITE_ERROR == status){
            puts("Can't select leading!\n");
            exit(1);
        }
        else if(SQLITE_DONE == status){
            break;
        }else{
            getLeading(stmt, leadings[count]);
            count++;
        }
    }

    sqlite3_finalize(stmt);
}
