#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "database.h"

int main(){
	const int size = 4;
	studentList_t * newStudentList = studentList_new(size);
	db_t * newDb = db_new("database.db");
    student_t * newStudent = student_new();

	int countSize = db_getSize(newDb);
	printf("ALL STUDENT: %i\n\n", countSize);
    puts("-------------------------------------------------------------");

    //db_readOld()
    db_readList(newDb, newStudentList);
	studentList_print(newStudentList);
	puts("-------------------------------------------------------------");


	//int countTask = db_readListTask(newDb, radioProgramsTask, salaryTask, newLeadingList);
	//printf("     TASK     \n\nLeading with numRadioPrograms > %i and salary < %i: %i\n\n", radioProgramsTask, salaryTask, countTask);


	//puts("     LEADING (BY INDEX 2)     \n");

	//if (newLeading != NULL) {
	//	leading_print(newLeading );
	//}
	//puts("-------------------------------------------------------------");

	//puts("     CREATE NEW LEADING     \n");
	//leading_fillL(newLeading , "Fedia", "Andrienko", "1997-11-06", 2, 4000, 10.0);
	//db_create(newDb, newLeading );
	//db_readList(newDb, newLeadingList);
	//leadingList_print(newLeadingList);
	//puts("-------------------------------------------------------------");

	//puts("     UPDATE LEADING (BY INDEX 2)     \n");
	//db_update(newDb, newStudent, 2);

	//puts("     DELETE LEADING (BY INDEX 3)     \n");
	//db_delete(newDb, 3);
	//db_readList(newDb, newLeadingList);
	//leadingList_print(newLeadingList);
	//puts("-------------------------------------------------------------");

	student_free(newStudent);
	studentList_free(newStudentList);
	db_free(newDb);
    return 0;
}
