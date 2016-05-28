#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "db.h"

int main(){
	const int size = 4;
	leadingList_t * newLeadingList = leadingList_new(size);
	db_t * newDb = db_new("database.db");

	int countSize = db_getSize(newDb);

	leading_t * newLeading;

	db_readList(newDb, newLeadingList);
	leadingList_print(newLeadingList);

	leading_free(newLeading );
	leadingList_free(newLeadingList);
	db_free(newDb);
    return 0;
}
