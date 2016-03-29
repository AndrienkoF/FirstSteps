#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include "func.h"

#define WHITE    FOREGROUND_RED   | FOREGROUND_BLUE      | FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define RED      FOREGROUND_RED   | FOREGROUND_INTENSITY
#define GREEN    FOREGROUND_GREEN | FOREGROUND_GREEN     | FOREGROUND_INTENSITY
#define YELLOW   FOREGROUND_RED   | FOREGROUND_GREEN     | FOREGROUND_INTENSITY
#define PURPLE   FOREGROUND_RED   | FOREGROUND_BLUE      | FOREGROUND_INTENSITY
#define AQUA     FOREGROUND_GREEN | FOREGROUND_BLUE      | FOREGROUND_INTENSITY

int main (){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    int i, num;
	srand(time(NULL));
	downloadStudent("myStudent.txt");
    downloadGroupSubject("mySubject.txt");
    downloadSubjectMark("myMark.txt");
    while (1) {
		system("cls");
        drawConsole();
        pos.X = 11;
        pos.Y = 6;
        SetConsoleCursorPosition(hConsole, pos);
        SetConsoleTextAttribute(hConsole, YELLOW);
        scanf("%i", &num);
        switch (num) {
		case 1:
		    drawSmile();
		    pos.X = 0;
            pos.Y = 17;
            SetConsoleCursorPosition(hConsole, pos);
            SetConsoleTextAttribute(hConsole, YELLOW);
			pushStudent();
			break;
		case 2:
		    drawSad();
            pos.X = 0;
            pos.Y = 17;
            SetConsoleCursorPosition(hConsole, pos);
            SetConsoleTextAttribute(hConsole, YELLOW);
			removeStudent();
			break;
		case 3:
		    drawSmile();
		    pos.X = 0;
            pos.Y = 17;
            SetConsoleCursorPosition(hConsole, pos);
            SetConsoleTextAttribute(hConsole, YELLOW);
			showStudent();
			getch();
			break;
		case 4:
		    drawSmile();
		    pos.X = 0;
            pos.Y = 17;
            SetConsoleCursorPosition(hConsole, pos);
            SetConsoleTextAttribute(hConsole, YELLOW);
			showSubject();
			getch();
			break;
		case 5:
		    drawSmile();
		    pos.X = 0;
            pos.Y = 17;
            SetConsoleCursorPosition(hConsole, pos);
            SetConsoleTextAttribute(hConsole, YELLOW);
			showMarks();
			getch();
			break;
		case 6:
		    drawSad();
		    pos.X = 0;
            pos.Y = 17;
            SetConsoleCursorPosition(hConsole, pos);
            SetConsoleTextAttribute(hConsole, YELLOW);
			showExceptionStudent();
			getch();
			break;
		case 7:
		    drawSmile();
		    pos.X = 0;
            pos.Y = 17;
            SetConsoleCursorPosition(hConsole, pos);
            SetConsoleTextAttribute(hConsole, YELLOW);
			newMark();
			break;
		case 8:
		    drawSmile();
		    pos.X = 0;
            pos.Y = 17;
            SetConsoleCursorPosition(hConsole, pos);
            SetConsoleTextAttribute(hConsole, YELLOW);
			saveToFile("myStudent.txt", "myMark.txt");
			exit(EXIT_SUCCESS);
		}
	}
	return 0;
}

