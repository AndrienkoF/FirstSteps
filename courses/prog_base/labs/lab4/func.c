#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include "func.h"
#define WHITE    FOREGROUND_RED   | FOREGROUND_BLUE      | FOREGROUND_GREEN     | FOREGROUND_INTENSITY
#define WHITE2   BACKGROUND_RED   | BACKGROUND_BLUE      | BACKGROUND_GREEN     | BACKGROUND_INTENSITY
#define RED      FOREGROUND_RED   | FOREGROUND_INTENSITY
#define RED2     BACKGROUND_RED   | BACKGROUND_INTENSITY
#define GREEN    FOREGROUND_GREEN | FOREGROUND_GREEN     | FOREGROUND_INTENSITY
#define YELLOW   FOREGROUND_RED   | FOREGROUND_GREEN     | FOREGROUND_INTENSITY
#define YELLOW2  BACKGROUND_RED   | BACKGROUND_GREEN     | BACKGROUND_INTENSITY
#define PURPLE   FOREGROUND_RED   | FOREGROUND_BLUE      | FOREGROUND_INTENSITY
#define AQUA     FOREGROUND_GREEN | FOREGROUND_BLUE      | FOREGROUND_INTENSITY
#define BLUE     FOREGROUND_BLUE  | FOREGROUND_INTENSITY

struct Subject {
        char nameS[20];
        int  mark;
    } listSubject;

    struct Group {
        char nameG[10];
        struct Subject ownSubject[4];
    } listGroup[2];

    struct Student {
        char name[20];
        char surname[20];
        int  age;
        char exception;
        struct Group ownGroup;
    } listStudent[50];


void consColor(int color){
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void drawForm(int n, int h, int xO, int yO, int start){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;

	switch (start){
        case 0:
            SetConsoleTextAttribute(hConsole, GREEN); break;
        case 1:
            SetConsoleTextAttribute(hConsole, GREEN); break;
    }
	int i;
	for (i = 0; i < n; i++){
		pos.X = xO + i;
		pos.Y = yO;
		SetConsoleCursorPosition(hConsole, pos);
		printf("==");
		pos.Y = yO + h;
		SetConsoleCursorPosition(hConsole, pos);
		printf("==");
	}
	for (i = 0; i <= h; i++){
		pos.X = xO;
		pos.Y = yO + i;
		SetConsoleCursorPosition(hConsole, pos);
		printf("|");
		pos.X = xO + n;
		SetConsoleCursorPosition(hConsole, pos);
		printf("|");
	}
	SetConsoleCursorPosition(hConsole, pos);
}

void drawConsole(void){
    int i;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    drawForm(50, 10, 10, 1, 0);

    SetConsoleTextAttribute(hConsole, RED);
	pos.X = 21;
	pos.Y = 2;
	SetConsoleCursorPosition(hConsole, pos);
	printf("Welcome to the university !  ");

	SetConsoleTextAttribute(hConsole, WHITE);
	pos.X = 11;
	pos.Y = 4;
	SetConsoleCursorPosition(hConsole, pos);
	printf("What do you want to do? Enter \"(HELP)\":");

    pos.X = 75;
	pos.Y = 1;
	SetConsoleCursorPosition(hConsole, pos);
	SetConsoleTextAttribute(hConsole, YELLOW);
	printf("HELP");

    pos.X = 65;
	pos.Y = 3;
	SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, YELLOW);
    printf("1 ");
    SetConsoleTextAttribute(hConsole, PURPLE);
    printf("- push new student;\n");

    pos.X = 65;
	pos.Y = 4;
	SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, YELLOW);
    printf("2 ");
    SetConsoleTextAttribute(hConsole, PURPLE);
    printf("- remove student;\n");

    pos.X = 65;
	pos.Y = 5;
	SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, YELLOW);
    printf("3 ");
    SetConsoleTextAttribute(hConsole, PURPLE);
    printf("- show all student list;\n");

    pos.X = 65;
	pos.Y = 6;
	SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, YELLOW);
    printf("4 ");
    SetConsoleTextAttribute(hConsole, PURPLE);
    printf("- show all subject list;\n");

    pos.X = 65;
	pos.Y = 7;
	SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, YELLOW);
    printf("5 ");
    SetConsoleTextAttribute(hConsole, PURPLE);
    printf("- show all mark list;\n");

    pos.X = 65;
	pos.Y = 8;
	SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, YELLOW);
    printf("6 ");
    SetConsoleTextAttribute(hConsole, PURPLE);
    printf("- show exception student;\n");

    pos.X = 65;
	pos.Y = 9;
	SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, YELLOW);
    printf("7 ");
    SetConsoleTextAttribute(hConsole, PURPLE);
    printf("- enter new mark;\n");

    pos.X = 65;
	pos.Y = 10;
	SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, YELLOW);
    printf("8 ");
    SetConsoleTextAttribute(hConsole, PURPLE);
    printf("- save student list to file and exit;\n");

    for (i = 0; i <= 131; i++){
		pos.X = i;
		pos.Y = 15;
		SetConsoleTextAttribute(hConsole, AQUA);
		SetConsoleCursorPosition(hConsole, pos);
		printf("*");
    }
    for (i = 0; i <= 15; i++){
		pos.X = 132;
		pos.Y = 15 - i;
		SetConsoleTextAttribute(hConsole, AQUA);
		SetConsoleCursorPosition(hConsole, pos);
		printf("*");
    }
}

void drawSmile(void){
    int i;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    for (i = 0; i <= 4; i++){
		pos.X = 85 + i;
		pos.Y = 20;
		SetConsoleTextAttribute(hConsole, YELLOW2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
    }
    for (i = 0; i <= 8; i++){
		pos.X = 85 - 2 + i;
		pos.Y = 21;
		SetConsoleTextAttribute(hConsole, YELLOW2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
    }
    for (i = 0; i <= 12; i++){
		pos.X = 85 - 4 + i;
		pos.Y = 22;
		SetConsoleTextAttribute(hConsole, YELLOW2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
    }
    for (i = 0; i <= 16; i++){
		pos.X = 85 - 6 + i;
		pos.Y = 23;
		SetConsoleTextAttribute(hConsole, YELLOW2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
    }
    for (i = 0; i <= 20; i++){
		pos.X = 85 - 8 + i;
		pos.Y = 24;
		SetConsoleTextAttribute(hConsole, YELLOW2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
    }
    for (i = 0; i <= 20; i++){
		pos.X = 85 - 8 + i;
		pos.Y = 25;
		SetConsoleTextAttribute(hConsole, YELLOW2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
    }
    for (i = 0; i <= 20; i++){
		pos.X = 85 - 8 + i;
		pos.Y = 26;
		SetConsoleTextAttribute(hConsole, YELLOW2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
    }
    for (i = 0; i <= 16; i++){
		pos.X = 85 - 6 + i;
		pos.Y = 27;
		SetConsoleTextAttribute(hConsole, YELLOW2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
    }
    for (i = 0; i <= 12; i++){
		pos.X = 85 - 4 + i;
		pos.Y = 28;
		SetConsoleTextAttribute(hConsole, YELLOW2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
    }
    for (i = 0; i <= 8; i++){
		pos.X = 85 - 2 + i;
		pos.Y = 29;
		SetConsoleTextAttribute(hConsole, YELLOW2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
    }
    for (i = 0; i <= 10; i++){
		pos.X = 87;
		pos.Y = 30 + i;
		SetConsoleTextAttribute(hConsole, WHITE2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
    }
    for (i = 0; i <= 6; i++){
		pos.X = 87 - i;
		pos.Y = 40 + i;
		SetConsoleTextAttribute(hConsole, WHITE2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
    }
    for (i = 0; i <= 6; i++){
		pos.X = 87 + i;
		pos.Y = 40 + i;
		SetConsoleTextAttribute(hConsole, WHITE2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
    }
    for (i = 0; i <= 6; i++){
		pos.X = 87 + i;
		pos.Y = 37 - i;
		SetConsoleTextAttribute(hConsole, WHITE2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
    }
    for (i = 0; i <= 6; i++){
		pos.X = 87 - i;
		pos.Y = 37 - i;
		SetConsoleTextAttribute(hConsole, WHITE2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
    }
		pos.X = 85 - 2;
		pos.Y = 23;
		SetConsoleTextAttribute(hConsole, RED2);
		SetConsoleCursorPosition(hConsole, pos);
		printf("  ");
		pos.X = 85 + 5;
		pos.Y = 23;
		SetConsoleTextAttribute(hConsole, RED2);
		SetConsoleCursorPosition(hConsole, pos);
		printf("  ");
		pos.X = 85 + 6;
		pos.Y = 26;
		SetConsoleTextAttribute(hConsole, RED2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
		pos.X = 85 - 2;
		pos.Y = 26;
		SetConsoleTextAttribute(hConsole, RED2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
		pos.X = 85 - 1;
		pos.Y = 27;
		SetConsoleTextAttribute(hConsole, RED2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
		pos.X = 85 + 5;
		pos.Y = 27;
		SetConsoleTextAttribute(hConsole, RED2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
		for (i = 0; i <= 4; i++){
            pos.X = 85 + + i;
            pos.Y = 28;
            SetConsoleTextAttribute(hConsole, RED2);
            SetConsoleCursorPosition(hConsole, pos);
            printf(" ");
		}
}

void drawSad(void){
    int i;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    for (i = 0; i <= 4; i++){
		pos.X = 85 + i;
		pos.Y = 20;
		SetConsoleTextAttribute(hConsole, YELLOW2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
    }
    for (i = 0; i <= 8; i++){
		pos.X = 85 - 2 + i;
		pos.Y = 21;
		SetConsoleTextAttribute(hConsole, YELLOW2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
    }
    for (i = 0; i <= 12; i++){
		pos.X = 85 - 4 + i;
		pos.Y = 22;
		SetConsoleTextAttribute(hConsole, YELLOW2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
    }
    for (i = 0; i <= 16; i++){
		pos.X = 85 - 6 + i;
		pos.Y = 23;
		SetConsoleTextAttribute(hConsole, YELLOW2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
    }
    for (i = 0; i <= 20; i++){
		pos.X = 85 - 8 + i;
		pos.Y = 24;
		SetConsoleTextAttribute(hConsole, YELLOW2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
    }
    for (i = 0; i <= 20; i++){
		pos.X = 85 - 8 + i;
		pos.Y = 25;
		SetConsoleTextAttribute(hConsole, YELLOW2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
    }
    for (i = 0; i <= 20; i++){
		pos.X = 85 - 8 + i;
		pos.Y = 26;
		SetConsoleTextAttribute(hConsole, YELLOW2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
    }
    for (i = 0; i <= 16; i++){
		pos.X = 85 - 6 + i;
		pos.Y = 27;
		SetConsoleTextAttribute(hConsole, YELLOW2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
    }
    for (i = 0; i <= 12; i++){
		pos.X = 85 - 4 + i;
		pos.Y = 28;
		SetConsoleTextAttribute(hConsole, YELLOW2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
    }
    for (i = 0; i <= 8; i++){
		pos.X = 85 - 2 + i;
		pos.Y = 29;
		SetConsoleTextAttribute(hConsole, YELLOW2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
    }
    for (i = 0; i <= 10; i++){
		pos.X = 87;
		pos.Y = 30 + i;
		SetConsoleTextAttribute(hConsole, WHITE2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
    }
    for (i = 0; i <= 6; i++){
		pos.X = 87 - i;
		pos.Y = 40 + i;
		SetConsoleTextAttribute(hConsole, WHITE2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
    }
    for (i = 0; i <= 6; i++){
		pos.X = 87 + i;
		pos.Y = 40 + i;
		SetConsoleTextAttribute(hConsole, WHITE2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
    }
    for (i = 0; i <= 6; i++){
		pos.X = 87 + i;
		pos.Y = 32 + i;
		SetConsoleTextAttribute(hConsole, WHITE2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
    }
    for (i = 0; i <= 6; i++){
		pos.X = 87 - i;
		pos.Y = 32 + i;
		SetConsoleTextAttribute(hConsole, WHITE2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
    }
        pos.X = 85 - 2;
		pos.Y = 24;
		SetConsoleTextAttribute(hConsole, BLUE | YELLOW2);
		SetConsoleCursorPosition(hConsole, pos);
		printf("//");
		pos.X = 85 + 5;
		pos.Y = 24;
		SetConsoleTextAttribute(hConsole, BLUE | YELLOW2);
		SetConsoleCursorPosition(hConsole, pos);
		printf("//");
		pos.X = 85 - 2;
		pos.Y = 23;
		SetConsoleTextAttribute(hConsole, RED2);
		SetConsoleCursorPosition(hConsole, pos);
		printf("  ");
		pos.X = 85 + 5;
		pos.Y = 23;
		SetConsoleTextAttribute(hConsole, RED2);
		SetConsoleCursorPosition(hConsole, pos);
		printf("  ");
		pos.X = 85 + 6;
		pos.Y = 27;
		SetConsoleTextAttribute(hConsole, RED2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
		pos.X = 85 - 2;
		pos.Y = 27;
		SetConsoleTextAttribute(hConsole, RED2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
		pos.X = 85 - 1;
		pos.Y = 26;
		SetConsoleTextAttribute(hConsole, RED2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
		pos.X = 85 + 5;
		pos.Y = 26;
		SetConsoleTextAttribute(hConsole, RED2);
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
		for (i = 0; i <= 4; i++){
            pos.X = 85 + i;
            pos.Y = 25;
            SetConsoleTextAttribute(hConsole, RED2);
            SetConsoleCursorPosition(hConsole, pos);
            printf(" ");
		}
}


void clear(void){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;

	pos.X = 21;
	pos.Y = 6;
	SetConsoleCursorPosition(hConsole, pos);
    printf("                              ");
}

int fileRows(const char * pread) {
	int i;
	int row = 0;
	FILE * fr = fopen(pread, "r");
	if ((fr = fopen(pread, "r")) == NULL) {
		printf("ERROR\n");
		return 0;
	}
	do {
		i = fgetc(fr);
		if (i == '\n') {
			row++;
		}
	} while (i != EOF);
	fclose(fr);
	return row;
}

void downloadStudent(const char * pread) {
    int i, rows;
	FILE * fr = fopen(pread, "r");
	if ((fr = fopen(pread, "r")) == NULL) {
		printf("ERROR\n");
		return;
	}
    char string[100];
	for (i = 0; i < 50; i++){
        listStudent[i].name[0] = '\0';
	}
	rows = fileRows("myStudent.txt");
	for (i = 0; i < rows; i++) {
		fgets(string, 100, fr);
		sscanf(string, "%s %s %i %c %s", &listStudent[i].name, &listStudent[i].surname, &listStudent[i].age, &listStudent[i].exception, &listStudent[i].ownGroup.nameG);
	}
	fclose(fr);
}

void downloadGroupSubject(const char * pread) {
	int i, j;
	char string[100];
	FILE * fr = fopen(pread, "r");
	if ((fr = fopen(pread, "r")) == NULL) {
		printf("ERROR");
		return;
	}
	for (i = 0; i < 2; i++) {
		fgets(string, 100, fr);
		sscanf(string, "%s %s %s %s", &listGroup[i].ownSubject[0].nameS, &listGroup[i].ownSubject[1].nameS, &listGroup[i].ownSubject[2].nameS, &listGroup[i].ownSubject[3].nameS);
	}
	fclose(fr);
}

void downloadSubjectMark(const char * pread) {
	int i, j, k, rows;
	char string[100];
	FILE * fr = fopen(pread, "r");
	if ((fr = fopen(pread, "r")) == NULL) {
		printf("ERROR");
		return;
	}
	rows = fileRows("myMark.txt");
	for (i = 0; i < rows; i++) {
		fgets(string, 100, fr);
		sscanf(string, "%i %i %i %i ", &listStudent[i].ownGroup.ownSubject[0].mark,&listStudent[i].ownGroup.ownSubject[1].mark, &listStudent[i].ownGroup.ownSubject[2].mark,&listStudent[i].ownGroup.ownSubject[3].mark);
	}
	fclose(fr);
}

int findRow(void) {
	int i;
	for (i = 0; listStudent[i].name[0] && i < 50; i++);
	if (i == 50) {
		return -1;
	}
	return i;
}

void pushStudent(void) {
	int i;
	int j;
	char str[100];
    j = findRow();
    if (j == -1) {
		printf("No memory!");
		return 0;
	}
	printf("New name: ");
	scanf("%s", &listStudent[j].name);
	printf("New surname: ");
	scanf("%s", &listStudent[j].surname);
	printf("New age: ");
	scanf("%s", &str);
	listStudent[j].age = atoi(str);
	printf("Enter exception (+ or -): ");
	scanf("%s", &listStudent[j].exception);
	printf("Enter group (KP-51 or KP-52): ");
	scanf("%s", &listStudent[j].ownGroup.nameG);

}

void removeStudent(void) {
	int i;
	char str[100];
	printf("Enter the number of student: ");
	scanf("%s", str);
    i = atoi(str);
	if (i >= 0 && i < 50) {
		listStudent[i].name[0] = '\0';
	}
}

void showStudent(void) {
	int i;
	for (i = 0; i < 50; i++) {
		if (listStudent[i].name[0] != '\0') {
			printf("%i) Name:        %s\n",   i, listStudent[i].name);
			printf("   Surname:     %s\n",   listStudent[i].surname);
			printf("   Age:         %i\n",   listStudent[i].age);
			printf("   Exception    %c\n",   listStudent[i].exception);
			printf("   Group:       %s\n\n",   listStudent[i].ownGroup.nameG);
		}
	}
}

void showSubject(void) {
	int i;
	printf("KP-51: \n");
	for (i = 0; i < 4; i++) {
		printf("%i. %s\n", i, listGroup[0].ownSubject[i].nameS);
	}
	puts("");
	printf("KP-52: \n");
	for (i = 0; i < 4; i++) {
		printf("%i. %s\n", i, listGroup[1].ownSubject[i].nameS);
	}
}

void showMarks(void) {
	int i, j;
	for (i = 0; i < 50; i++) {
		if (listStudent[i].name[0] != '\0') {
			printf("%i. %s %s (%s):\n", i, listStudent[i].name, listStudent[i].surname,
          listStudent[i].ownGroup.nameG);
			if (strcmp(listStudent[i].ownGroup.nameG, "KP-51") == 0) {
				for (j = 0; j < 4; j++) {
					printf("%i) %s: %i\n", j, listGroup[0].ownSubject[j].nameS,
            listStudent[i].ownGroup.ownSubject[j].mark);
				}
				puts("");
			}
			else if (strcmp(listStudent[i].ownGroup.nameG, "KP-52") == 0) {
				for (j = 0; j < 4; j++) {
					printf("%i) %s: %i\n", j, listGroup[1].ownSubject[j].nameS,
            listStudent[i].ownGroup.ownSubject[j].mark);
				}
				puts("");
			}
        }
    }
}

void newMark(void) {
	showMarks();
	int num, num2;
	char str[10];
	char str1[10];
	char str2[10];
	int mark;
	printf("Enter the number of student:\n");
	scanf("%s", &str);
	num = atoi(str);
    printf("Enter the number of subject:\n");
    scanf("%s", &str1);
    num2 = atoi(str1);
    printf("Enter the mark:\n");
    scanf("%s", &str2);
    mark = atoi(str2);
    listStudent[num].ownGroup.ownSubject[num2].mark = mark;
}

void showExceptionStudent(void){
    int i;
	printf("Students, who will be returned home:\n\n");
	for (i = 0; i < 50; i++) {
		if (listStudent[i].name[0] != '\0' && listStudent[i].exception == '-') {
			printf("%s %s\n", listStudent[i].name, listStudent[i].surname);
		}
	}
}

void saveToFile(const char * pwrite1, const char * pwrite2) {
	int i;
	FILE * fw1 = fopen(pwrite1, "w");
	FILE * fw2 = fopen(pwrite2, "w");
	if ((fw1 = fopen(pwrite1, "w")) == NULL || (fw2 = fopen(pwrite2, "w")) == NULL) {
		printf("ERROR!\n");
	}
	for (i = 0; i < 50; i++) {
		if (listStudent[i].name[0] != '\0') {
			fprintf(fw1, "%s %s %i %c %s\n", listStudent[i].name, listStudent[i].surname,
           listStudent[i].age, listStudent[i].exception, listStudent[i].ownGroup.nameG);
			fprintf(fw2, "%i %i %i %i\n", listStudent[i].ownGroup.ownSubject[0].mark,
           listStudent[i].ownGroup.ownSubject[1].mark,
           listStudent[i].ownGroup.ownSubject[2].mark,
           listStudent[i].ownGroup.ownSubject[3].mark);
		}
	}
	fclose(fw1);
	fclose(fw2);
}


#endif // FUNC_H_INCLUDED
