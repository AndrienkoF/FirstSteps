#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#define WHITE    FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_GREEN
#define PURPLE   FOREGROUND_RED | FOREGROUND_BLUE                    | FOREGROUND_INTENSITY
#define YELLOW   FOREGROUND_RED | FOREGROUND_GREEN                   | FOREGROUND_INTENSITY

void consColor(int color)
{
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void fillRand (int n, double mat[n][n], float MIN, float MAX)
{
    int  i, j;
    for (i = 0; i < n ; i++)
    {
        for (j = 0; j < n ; j++)
        {
            mat[i][j] = (double)rand() / (double)RAND_MAX * (MAX - MIN) + MIN;
        }
    }
}

void copyMatrix(int n, double mat[n][n], double mat2[n][n])
{
	int i, j;
	for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
                {
                    mat2[i][j] = mat[i][j];
                }
        }
}

void printMatrix (int n, double mat [n][n], double mat2 [n][n])
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;

    int i, j;
    for (i = 0; i < n ; i++)
    {
        pos.X = 1;
		pos.Y = 1 + i;
		SetConsoleCursorPosition(hConsole, pos);
		printf("\t");
        SetConsoleTextAttribute(hConsole, WHITE | BACKGROUND_GREEN);
        for (j = 0; j < n ; j++)
        {
            if (mat[i][j] != mat2[i][j])
                {
                    SetConsoleTextAttribute(hConsole, WHITE | BACKGROUND_GREEN);
                }
            printf("%6.2f\t", mat[i][j]);
            SetConsoleTextAttribute(hConsole, WHITE | BACKGROUND_GREEN);

        }
    }
    copyMatrix(n, mat, mat2);
}

void zeroMatrix(int n, double mat [n][n])
{
    int i,j;
    for ( i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            mat[i][j] = 0;
        }
    }
}

void exchange(int n, double mat[n][n], int index1, int index2, float num)
{
    mat[index1][index2] = num;
}

void flipV (int n, double mat[n][n])
{
    int i, j;
    double result[n][n];
    for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
		{
            result [i][j] = mat[(n-1)-i][j] ;
		}

		for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
            mat[i][j] = result [i][j]  ;
		}
}

void turnVidDiag (int n, double mat [n][n])
{
    int i, j;
    double result[n][n];
    for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
		{
            result [i][j] = mat[j][i] ;
		}

		for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
            mat[i][j] = result [i][j]  ;
		}
}

void turn180 (int n, double mat[n][n])
{
    int i, j;
    double result[n][n];
    for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
		{
            result [i][j] = mat[(n-1)-i][(n-1)-j] ;
		}

		for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
            mat[i][j] = result [i][j]  ;
		}
}

void flipH(int n, double mat[n][n])
{
    int i, j;
	double result[n][n] ;

		for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
            result [i][j] =  mat[i][(n-1) - j];
		}

		for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
            mat[i][j] = result [i][j] ;
		}

}

float sumMatrix (int n, double mat[n][n])
{
    int i,j;
    float sum = 0;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            sum += mat[i][j];
        }
    }
    return sum;
}

float sumR (int n, double mat[n][n], int indexR)
{
    int j;
	float sum2 = 0;
	for (j = 0; j < n; j++)
    {
		sum2 += mat[indexR][j];
	}
	return sum2;
}

float sumDiag (int n, double mat[n][n])
{
    int i,j;
    float sum3 = 0;
    for (i = 0; i < n; i++)
    {
        for (j = 0 + i; j < n; j++)
        {
            sum3 += mat[i][j];
        }
    }
    return sum3;
}

void findMaxMin( int n, double mat[n])
{
    int i, j;
	int nMin = 0;
	int nMax = 0;
	float Min = mat[0];
	float Max = mat[0];
	double temp = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (mat[i*n + j] <= Min)
                {
					Min = mat[i*n + j];
					nMin = i*n + j;
				}
            else if (mat[i*n + j] >= Max) {
					Max = mat[i*n + j];
					nMax = i*n + j;
                }
        }
    }
	temp = mat[nMin];
	mat[nMin] = mat[nMax];
	mat[nMax] = temp;
}

void findMaxMin2( int n, double mat[n])
{
    int i, j;
	int nMin = 0;
	int nMax = 0;
	float Min = mat[0];
	float Max = mat[0];
	double temp = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (mat[i*n + j] < Min)
                {
					Min = mat[i*n + j];
					nMin = i*n + j;
				}
            else if (mat[i*n + j] >= Max) {
					Max = mat[i*n + j];
					nMax = i*n + j;
                }
        }
    }
	temp = mat[nMin];
	mat[nMin] = mat[nMax];
	mat[nMax] = temp;
}

void findColumn(int n, double mat[n])
{
	int i, j;
	float sum = 0;
	float sumMin = 0;
	float sumMax = 0;
	for (i = 0; i < n; i++)
    {
		sumMin = sumMin + mat[i*n];
	}
	sumMax = sumMin;
	int nMin = 0;
	int nMax = 0;
	double temp = 0;
	for (j = 1; j < n; j++)
	{
		for (i = 0; i < n; i++)
		{
			sum = sum + mat[j + i*n];
		}
			if (sum < sumMin)
			{
				sumMin = sum;
				nMin = j;
			}
			if (sum >= sumMax)
			{
				sumMax = sum;
				nMax = j;
			}
			sum = 0;
	}
	for (i = 0; i < n; i++)
	{
		temp = mat[i*n + nMin];
		mat[i*n + nMin] = mat[i*n + nMax];
		mat[i*n + nMax] = temp;
	}
}


void drawForm(int n, int h, int xO, int yO, int start)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;

	switch (start)
	{
        case 0:
            SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN); break;
        case 1:
            SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN); break;
    }
	int i;
	for (i = 0; i < n; i++)
    {
		pos.X = xO + i;
		pos.Y = yO;
		SetConsoleCursorPosition(hConsole, pos);
		printf("==");
		pos.Y = yO + h;
		SetConsoleCursorPosition(hConsole, pos);
		printf("==");
	}
	for (i = 0; i <= h; i++)
	{
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

void drawFill(int n, int h, int xO, int yO, int start)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;

	switch (start)
	{
        case 0:
            SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN ); break;
        case 1:
            SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN); break;
    }
	int i, j;
	pos.X = xO + 1;
	pos.Y = yO + 1;
	for (i = 0; i < n; i++)
        {
            for (j = 0; j < h - 1; j++)
            {
                pos.Y = yO + 1 + j;
                SetConsoleCursorPosition(hConsole, pos);
                printf(" ");
            }
            pos.X = xO + 1 + i;
            pos.Y = yO + 1;
        }
    SetConsoleCursorPosition(hConsole, pos);
}

void newForm(int n, double mat[n][n], double mat2[n][n])
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;

	pos.X = 1;
	pos.Y = 1;
	drawFill(60, 10, 0, 0, 1);
	pos.X = 10;
	pos.Y = 1;
	SetConsoleCursorPosition(hConsole, pos);
	printMatrix (n, mat, mat2);
	pos.X = 2;
	pos.Y = 18;
	SetConsoleCursorPosition(hConsole, pos);
	SetConsoleTextAttribute(hConsole, WHITE || BACKGROUND_GREEN);
	printf("                                                                              ");
    SetConsoleCursorPosition(hConsole, pos);
}

void clear(void)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
	int i;
	pos.X = 15;
	pos.Y = 12;
	SetConsoleCursorPosition(hConsole, pos);
	for (i = 0; i <= 2; i++){
    printf("                                                                                                                                              \n");
	}
}


int main(void)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;

    int n ,i,j;
    int check ;
    int indexR;
    char nums[3][3];
    srand(time(NULL));

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    drawForm(50, 7, 20, 5, 0);
    drawFill(50, 7, 20, 5, 0);
    SetConsoleTextAttribute(hConsole, WHITE);
	pos.X = 21;
	pos.Y = 7;
	SetConsoleCursorPosition(hConsole, pos);
	printf("Enter matrix size (1 to 6): ");
	do
	{
	    check = scanf("%s", &nums[0]);
		n = atoi(nums[0]);
		if (n <= 0 || n >=7 )
        {
			pos.X = 21;
			pos.Y = 9;
			SetConsoleCursorPosition(hConsole, pos);
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN );
			printf("ERROR, try again !\n");
			pos.X = 21;
			pos.Y = 10;
			SetConsoleCursorPosition(hConsole, pos);
			printf("                                     ");
			pos.X = 21;
			pos.Y = 10;
			SetConsoleCursorPosition(hConsole, pos);
			SetConsoleTextAttribute(hConsole, WHITE | BACKGROUND_GREEN );
			check = 0;
		}
	} while ( check < 1);

	double mat[n][n];
    double mat2[n][n];
    zeroMatrix( n, mat);
    SetConsoleTextAttribute(hConsole, WHITE || BACKGROUND_GREEN  );
	system("cls");
	drawForm(60, 10, 0, 0, 1);
    drawFill(60, 10, 0, 0, 1);
    fillRand ( n, mat, -2.55, 5.23);
	pos.X = 10;
	pos.Y = 1;
	SetConsoleCursorPosition(hConsole, pos);
	printMatrix (n, mat, mat2);

    pos.X = 5;
	pos.Y = 19;
	SetConsoleCursorPosition(hConsole, pos);
	SetConsoleTextAttribute(hConsole, YELLOW);
	printf("HELP");

    pos.X = 0;
	pos.Y = 20;
	SetConsoleCursorPosition(hConsole, pos);
	SetConsoleTextAttribute(hConsole, PURPLE);
    printf("zero        - reset all elements of the matrix;\n");
    printf("rand x x    - range [MIN ; MAX];\n");
	printf("rep [x;x] x - replace the element of the array by index;\n");
	printf("flipV       - flip vertically;\n");
	printf("flipH       - flip horizontally;\n");
	printf("turnVD      - show respect to the main diagonal;\n");
	printf("turn180     - rotate 180 degrees;\n");
	printf("sumM        - print the amount of matrix elements;\n");
	printf("sumR x      - the sum of the elements of a given line;\n");
	printf("sumD        - the sum of the elements above the main diagonal (with diagonal elements);\n");
	printf("MaxMin      - change the  1maximum <-> 1minimum matrix elements;\n");
	printf("MaxMin2     - change the  1maximum <-> minimum matrix elements;\n");
	printf("findC       - column with the greatest amount <-> least amount;\n");
    printf("exit        - close program;\n");

    pos.X = 0;
	pos.Y = 12;
	SetConsoleCursorPosition(hConsole, pos);
	SetConsoleTextAttribute(hConsole, YELLOW);
	printf("Enter command: ");

	while (1)
        {
            SetConsoleTextAttribute(hConsole, PURPLE);
            pos.X = 15;
            pos.Y = 12;
            SetConsoleCursorPosition(hConsole, pos);
            scanf("%s", &nums[0]);
            puts("");
            if (strcmp(nums[0], "zero") == 0)
                {
                    zeroMatrix( n, mat);
                    newForm( n, mat, mat2);
                    clear();
                }
            else if (strcmp(nums[0], "rand") == 0)
                {
                    float MAX , MIN ;
                    scanf("%f %f", &MIN, &MAX);
                    if (MAX < MIN)
                    {
                        pos.X = 0;
                        pos.Y = 13;
                        SetConsoleCursorPosition(hConsole, pos);
                        printf("ERROR, try again");
                        pos.X = 0;
                        pos.Y = 14;
                        SetConsoleCursorPosition(hConsole, pos);
                        printf("Press any key to continue...\n");
                        getch();
                        clear();
                        continue;
                    }
                    pos.X = 0;
                    pos.Y = 13;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Diapason:[%.2f ; %.2f]", MIN, MAX);
                    pos.X = 0;
                    pos.Y = 14;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Press any key to continue...\n");
                    getch();
                    fillRand ( n, mat, MIN, MAX);
                    newForm( n, mat, mat2);
                    clear();
                }
            else if (strcmp(nums[0], "rep") == 0)
                {
                    int index1, index2;
                    float num = 0;
                    scanf("%s %s %f", &nums[1], &nums[2], &num);
                    index1 = atoi(nums[1]);
                    index2 = atoi(nums[2]);
                    if ((index1 > n - 1 || index1 < 0) || (index2 > n - 1 || index2 < 0))
                        {
                            printf("ERROR, try again\n");
                            printf("Press any key to continue...\n");
                            getch();
                            clear();
                            continue;
                        }
                    else
                    {
                        exchange (n, mat , index1, index2 , num);
                        newForm( n, mat, mat2);
                        clear();

                    }
			}
            else if (strcmp(nums[0], "flipV") == 0)
                {
                    flipV ( n, mat);
                    newForm( n, mat, mat2);
                    clear();
                }
            else if (strcmp(nums[0], "flipH") == 0)
                {
                    flipH( n,  mat);
                    newForm( n, mat, mat2);
                    clear();
                }
            else if (strcmp(nums[0], "turnVD") == 0)
                {
                    turnVidDiag ( n, mat);
                    newForm( n, mat, mat2);
                    clear();
                }
            else if (strcmp(nums[0], "turn180") == 0)
                {
                    turn180 ( n, mat);
                    newForm( n, mat, mat2);
                    clear();
                }
            else if (strcmp(nums[0], "sumM") == 0)
                {
                    float sum = 0;
                    sum = sumMatrix  (n, mat);
                    printf("%.2f\n", sum);
                    printf("Press any key to continue...");
                    getch();
                    clear();
                }
            else if (strcmp(nums[0], "sumR") == 0)
                {
                    float sum1 = 0;
                    scanf("%s", &nums[1]);
                    indexR = atoi(nums[1]);
                    sum1 = sumR ( n,  mat, indexR);
                    printf("%.2f\n", sum1);
                    printf("Press any key to continue...");
                    getch();
                    clear();
                }
            else if (strcmp(nums[0], "sumD") == 0)
                {
                    float sum2 = 0;
                    sum2 = sumDiag  (n, mat);
                    printf("%.2f\n", sum2);
                    printf("Press any key to continue...");
                    getch();
                    clear();
                }
            else if (strcmp(nums[0], "exit") == 0)
                {
                    SetConsoleTextAttribute(hConsole, YELLOW);
                    system("cls");
                    printf("Goodbye!!!");
                    puts("\n");
                    exit(0);
                    }
             else if (strcmp(nums[0], "MaxMin") == 0)
                {
                    findMaxMin( n, mat);
                    newForm( n, mat, mat2);
                    clear();
                }
            else if (strcmp(nums[0], "MaxMin2") == 0)
                {
                    findMaxMin( n, mat);
                    newForm( n, mat, mat2);
                    clear();
                }
            else if (strcmp(nums[0], "findC") == 0)
                {
                    findColumn( n, mat);
                    newForm( n, mat, mat2);
                    clear();
                }

            else
                {
                    pos.X = 0;
                    pos.Y = 13;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("ERROR, try again\n");
                    printf("Press any key to continue...");
                    getch();
                    clear();
                }

        }

    return 0;
}

