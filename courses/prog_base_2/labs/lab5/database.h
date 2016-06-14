#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include "leading/leading.h"
#include <stdbool.h>

typedef struct db_s db_t;

db_t * db_new(const char * dbFileName);
void db_free(db_t * db_data);

void db_insertLeading(db_t* db_data, leading_t* leading);
leading_t * db_getLeadingById(db_t* database, unsigned int id);
bool db_checkId(db_t*, unsigned int);
void db_fillLeadingArr(db_t*, leading_t**);

void db_deleteLeading(db_t* database, unsigned int id);
int db_countLeadings(db_t* database);
char* db_personalTask(db_t* base, char* salaryReq, int salaryVal, char* yearReq, int yearVal, leading_t** leadings);


#endif // DATABASE_H_INCLUDED
