#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "database.h"

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
	char * sqlRequest = "SELECT COUNT(*) FROM Student;";
	sqlite3_prepare_v2(newDb->db, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);
	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		printf("Cannot get size of Student table.\n");
		exit(1);
    }
	int size = sqlite3_column_int(stmt, 0);
	sqlite3_finalize(stmt);
	return size;
}

void student_fill(sqlite3_stmt * stmt, student_t * newStudent) {
	int id = sqlite3_column_int(stmt, 0);
	char * name = sqlite3_column_text(stmt, 1);
	char * surname = sqlite3_column_text(stmt, 2);
	char * fatherName = sqlite3_column_text(stmt, 3);
	char * birthdate = sqlite3_column_text(stmt, 4);
	char * hometown = sqlite3_column_text(stmt, 5);
	newStudent->id = id;
	strcpy(newStudent->name, name);
	strcpy(newStudent->surname, surname);
	strcpy(newStudent->fatherName, fatherName);
	strcpy(newStudent->birthdate, birthdate);
	strcpy(newStudent->hometown, hometown);
}

void db_create(db_t * newDb, student_t * newStudent) {
	sqlite3_stmt * stmt = NULL;
	char * sqlRequest = "INSERT INTO Student ('name', 'surname', 'fatherName', 'birthday', 'hometown') VALUES (?, ?, ?, ?, ?);";
	sqlite3_prepare_v2(newDb->db, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);
	sqlite3_bind_text(stmt, 1, newStudent->name, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, newStudent->surname, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, newStudent->fatherName, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 4, newStudent->birthdate, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 5, newStudent->hometown, -1, SQLITE_STATIC);
	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		printf("Cannot create new student.\n");
	}else {
		newStudent->id = sqlite3_last_insert_rowid(newDb->db);
		sqlite3_finalize(stmt);
	}
}

student_t * db_read(const db_t * newDb, int index) {
	sqlite3_stmt * stmt = NULL;
	student_t * newStudent = student_new();
	char * sqlRequest = "SELECT * FROM Student WHERE id = ?;";
	sqlite3_prepare_v2(newDb->db, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, index);
	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		printf("Cannot get Student with this id.\n");
		return NULL;
	}
	student_fill(stmt, newStudent);
	sqlite3_finalize(stmt);
	return newStudent;
}

student_t * db_readOld(const db_t * newDb, int index) {
	sqlite3_stmt * stmt = NULL;
	student_t * newStudent = student_new();
	char * sqlRequest = "SELECT * FROM Student WHERE fatherName = ?;";
	sqlite3_prepare_v2(newDb->db, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, index);
	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		printf("Cannot get Student with this id.\n");
		return NULL;
	}
	student_fill(stmt, newStudent);
	sqlite3_finalize(stmt);
	return newStudent;
}

void db_readList(const db_t * newDb, studentList_t * newStudentList) {
	sqlite3_stmt * stmt = NULL;
	int size = db_getSize(newDb);
	newStudentList->list = realloc(newStudentList->list, size * sizeof(student_t *));
	for (int i = 0; i < size; i++){
		newStudentList->list[i] = student_new();
	}
	newStudentList->size = size;
	char * sqlRequest = "SELECT * FROM Student;";
	sqlite3_prepare_v2(newDb->db, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);

	for (int i = 0; i < size; i++) {
		int rc = sqlite3_step(stmt);
		if (rc == SQLITE_ERROR) {
			printf("Cannot get Student table.\n");
			exit(1);
		}else {
			student_fill(stmt, newStudentList->list[i]);
		}
	}
	sqlite3_finalize(stmt);
}
////////////////////////////////////////TASK//////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/*
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
}*/

void db_update(db_t * newDb, student_t * newStudent, int index) {
	sqlite3_stmt * stmt = NULL;
	char * sqlRequest = "UPDATE student SET name = ?, surname = ?, fatherName = ?, birthday = ?, hometown = ? WHERE id = ?;";
	sqlite3_prepare_v2(newDb->db, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);

	sqlite3_bind_text(stmt, 1, newStudent->name, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, newStudent->surname, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, newStudent->fatherName, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 4, newStudent->birthdate, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 5, newStudent->hometown, -1, SQLITE_STATIC);
	sqlite3_bind_int(stmt, 6, index);
	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		printf("Cannot update this student.\n");
	}else{
		sqlite3_finalize(stmt);
	}
}

void db_delete(db_t * newDb, int index) {
	sqlite3_stmt * stmt = NULL;
	char * sqlRequest = "DELETE FROM Student WHERE id = ?;";
	sqlite3_prepare_v2(newDb->db, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);

	sqlite3_bind_int(stmt, 1, index);

	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		printf("Cannot delete this student.\n");
	}else {
		sqlite3_finalize(stmt);
	}
}
