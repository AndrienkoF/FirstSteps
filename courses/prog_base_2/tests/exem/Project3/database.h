#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include "sqlite3.h"
#include "student.h"

typedef struct db_s db_t;

db_t * db_new(const char * dbFile);
void db_free(db_t * newDb);
int db_getSize(const db_t * newDb);
void db_create(db_t * newDb, student_t * newStudent);
void db_readList(const db_t * newDb, studentList_t * newStudentList);
void db_update(db_t * newDb, student_t * newStudent, int index);
void db_delete(db_t * newDb, int index);


#endif // DATABASE_H_INCLUDED
