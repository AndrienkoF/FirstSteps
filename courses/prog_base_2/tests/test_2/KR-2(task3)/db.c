#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "db.h"

struct db_s {
	sqlite3 * db;
};

db_t * db_new(const char * dbFile) {
    db_t * newDb = malloc(sizeof(struct db_s));
    int rc = sqlite3_open(dbFile, & newDb->db);
    if (SQLITE_ERROR == rc) {
        printf("can't open database\n");
        exit(1);
    }
    return newDb;
}

void db_free(db_t * newDb) {
    sqlite3_close(newDb->db);
    free(newDb);
}

int db_getSize(const db_t * newDb) {
	sqlite3_stmt * stmt = NULL;
	char * sqlRequest = "SELECT COUNT(*) FROM Leading;";
	sqlite3_prepare_v2(newDb->db, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);
	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		printf("Cannot get size of Leading table.\n");
		exit(1);
    }
	int size = sqlite3_column_int(stmt, 0);
	sqlite3_finalize(stmt);
	return size;
}

void leading_fill(sqlite3_stmt * stmt, leading_t * newLeading) {
	int id = sqlite3_column_int(stmt, 0);
	char * name = sqlite3_column_text(stmt, 1);
	char * surname = sqlite3_column_text(stmt, 2);
	char * birthdate = sqlite3_column_text(stmt, 3);
	int numRadioPrograms = sqlite3_column_int(stmt, 4);
	int salary = sqlite3_column_int(stmt, 5);
	double rating = sqlite3_column_double(stmt, 6);
	newLeading->id = id;
	strcpy(newLeading->name, name);
	strcpy(newLeading->surname, surname);
	strcpy(newLeading->birthdate, birthdate);
	newLeading->numRadioPrograms = numRadioPrograms;
	newLeading->salary = salary;
	newLeading->rating = (float)rating;
}

void db_create(db_t * newDb, leading_t * newLeading) {
	sqlite3_stmt * stmt = NULL;
	char * sqlRequest = "INSERT INTO Leading ('name', 'surname', 'birthday', 'numRadioPrograms', 'salary', 'rating') VALUES (?, ?, ?, ?, ?, ?);";
	sqlite3_prepare_v2(newDb->db, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);
	sqlite3_bind_text(stmt, 1, newLeading->name, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, newLeading->surname, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, newLeading->birthdate, -1, SQLITE_STATIC);
	sqlite3_bind_int(stmt, 4, newLeading->numRadioPrograms);
	sqlite3_bind_int(stmt, 5, newLeading->salary);
	sqlite3_bind_double(stmt, 6, (float)newLeading->rating);
	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		printf("Cannot create new leading.\n");
	}else {
		newLeading->id = sqlite3_last_insert_rowid(newDb->db);
		sqlite3_finalize(stmt);
	}
}

leading_t * db_read(const db_t * newDb, int index) {
	sqlite3_stmt * stmt = NULL;
	leading_t * newLeading = leading_new();
	char * sqlRequest = "SELECT * FROM Leading WHERE id = ?;";
	sqlite3_prepare_v2(newDb->db, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, index);
	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		printf("Cannot get Leading with this id.\n");
		return NULL;
	}
	leading_fill(stmt, newLeading);
	sqlite3_finalize(stmt);
	return newLeading;
}

void db_readList(const db_t * newDb, leadingList_t * newLeadingList) {
	sqlite3_stmt * stmt = NULL;
	int size = db_getSize(newDb);
	newLeadingList->list = realloc(newLeadingList->list, size * sizeof(leading_t *));
	for (int i = 0; i < size; i++) {
		newLeadingList->list[i] = leading_new();
	}
	newLeadingList->size = size;
	char * sqlRequest = "SELECT * FROM Leading;";
	sqlite3_prepare_v2(newDb->db, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);

	for (int i = 0; i < size; i++) {
		int rc = sqlite3_step(stmt);
		if (rc == SQLITE_ERROR) {
			printf("Cannot get Leading table.\n");
			exit(1);
		}else {
			leading_fill(stmt, newLeadingList->list[i]);
		}
	}
	sqlite3_finalize(stmt);
}

int db_readListTask(const db_t * newDb, int numRadioPrograms, int salary, leadingList_t * newLeadingList) {
	sqlite3_stmt * stmt = NULL;
	char * sqlRequest = "SELECT COUNT(*) FROM Leading WHERE numRadioPrograms > ? AND salary < ?;";
	sqlite3_prepare_v2(newDb->db, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, numRadioPrograms);
	sqlite3_bind_int(stmt, 2, salary);
	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		printf("Cannot get size of Leading table.\n");
		exit(1);
	}
	int sizeFilter = sqlite3_column_int(stmt, 0);
	sqlite3_reset(stmt);
	newLeadingList->list = realloc(newLeadingList->list, sizeFilter * sizeof(leading_t *));
	for (int i = 0; i < sizeFilter; i++) {
		newLeadingList->list[i] = leading_new();
	}
	newLeadingList->size = sizeFilter;
	sqlRequest = "SELECT * FROM Leading WHERE numRadioPrograms > ? AND salary < ?;";
	sqlite3_prepare_v2(newDb->db, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, numRadioPrograms);
	sqlite3_bind_int(stmt, 2, salary);
	for (int i = 0; i < sizeFilter;i++) {
        rc = sqlite3_step(stmt);
		if (rc == SQLITE_ERROR) {
			printf("Cannot get Leading table.\n");
			exit(1);
		}else {
			leading_fill(stmt, newLeadingList->list[i]);
		}
	}
	sqlite3_finalize(stmt);
	return sizeFilter;
}

void db_update(db_t * newDb, leading_t * newLeading, int index) {
	sqlite3_stmt * stmt = NULL;
	char * sqlRequest = "UPDATE Leading SET name = ?, surname = ?, birthday = ?, numRadioPrograms = ?, salary = ?, rating = ? WHERE id = ?;";
	sqlite3_prepare_v2(newDb->db, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);

	sqlite3_bind_text(stmt, 1, newLeading->name, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, newLeading->surname, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, newLeading->birthdate, -1, SQLITE_STATIC);
	sqlite3_bind_int(stmt, 4, newLeading->numRadioPrograms);
	sqlite3_bind_int(stmt, 5, newLeading->salary);
	sqlite3_bind_double(stmt, 6, (double)newLeading->rating);
	sqlite3_bind_int(stmt, 7, index);
	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		printf("Cannot update this leading.\n");
	}else{
		sqlite3_finalize(stmt);
	}
}

void db_delete(db_t * newDb, int index) {
	sqlite3_stmt * stmt = NULL;
	char * sqlRequest = "DELETE FROM Leading WHERE id = ?;";
	sqlite3_prepare_v2(newDb->db, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);

	sqlite3_bind_int(stmt, 1, index);

	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		printf("Cannot delete this leading.\n");
	}else {
		sqlite3_finalize(stmt);
	}
}
