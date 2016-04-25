#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "database.h"

int main(){
	const int size = 4;
	leadingList_t * newLeadingList = leadingList_new(size);
	db_t * newDb = db_new("database.db");

	int countSize = db_getSize(newDb);
	printf("ALL LEADING: %i\n\n", countSize);
    puts("-------------------------------------------------------------");

	int radioProgramsTask = 1;
	int salaryTask = 4000;
	int countTask = db_readListTask(newDb, radioProgramsTask, salaryTask, newLeadingList);
	printf("     TASK     \n\nLeading with numRadioPrograms > %i and salary < %i: %i\n\n", radioProgramsTask, salaryTask, countTask);
	leadingList_print(newLeadingList);
    puts("-------------------------------------------------------------");

	puts("     LEADING (BY INDEX 2)     \n");
	leading_t * newLeading = db_read(newDb, 2);
	if (newLeading != NULL) {
		leading_print(newLeading );
	}
	puts("-------------------------------------------------------------");

	puts("     CREATE NEW LEADING     \n");
	leading_fillL(newLeading , "Fedia", "Andrienko", "1997-11-06", 2, 4000, 10.0);
	db_create(newDb, newLeading );
	db_readList(newDb, newLeadingList);
	leadingList_print(newLeadingList);
	puts("-------------------------------------------------------------");

	puts("     UPDATE LEADING (BY INDEX 2)     \n");
	db_update(newDb, newLeading , 2);
	db_readList(newDb, newLeadingList);
	leadingList_print(newLeadingList);
	puts("-------------------------------------------------------------");

	puts("     DELETE LEADING (BY INDEX 3)     \n");
	db_delete(newDb, 3);
	db_readList(newDb, newLeadingList);
	leadingList_print(newLeadingList);
	puts("-------------------------------------------------------------");

	leading_free(newLeading );
	leadingList_free(newLeadingList);
	db_free(newDb);
    return 0;
}
