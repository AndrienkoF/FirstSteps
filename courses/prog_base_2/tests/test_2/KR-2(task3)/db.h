#ifndef DB_H_INCLUDED
#define DB_H_INCLUDED

#include "sqlite3.h"
#include "leading.h"
#include "list.h"

typedef struct db_s db_t;

db_t * db_new(const char * dbFile);
void db_free(db_t * newDb);
int db_getSize(const db_t * newDb);
void db_create(db_t * newDb, leading_t * newLeading);
void db_create(db_t * newDb, leading_t * newLeading);
leading_t * db_read(const db_t * newDb, int index);
void db_readList(const db_t * newDb, leadingList_t * newLeadingList);
int db_readListTask(const db_t * newDb, int numRadioPrograms, int salary, leadingList_t * newLeadingList);
void db_update(db_t * newDb, leading_t * newLeading, int index);
void db_delete(db_t * newDb, int index);



#endif // DB_H_INCLUDED
