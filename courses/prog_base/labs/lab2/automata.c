#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int run(int moves[], int movesLen, int res[], int resLen)
{
    enum position
 {
    q0 = 0,
    q1,
    q2,
    q3
 };
    int mas1[4][302];
    int mas2[4][302];
    int move = 0;
    int point = 0;
    int active;
    int n = 0;
    int i;
    int j = 0;

    mas1[q0][4] = 1;
    mas2[q0][4] = 1;
    mas1[q0][16] = 'repeat';
    mas2[q0][16] = 1;
    mas1[q0][31] = 8;
    mas2[q0][31] = 0;
    mas1[q0][301] = 'break';

    mas1[q1][4] = 'pop';
    mas2[q1][4] = 3;
    mas1[q1][16] = 2;
    mas2[q1][16] = 2;
    mas1[q1][31] = 99;
    mas1[q1][301] = 5;
    mas2[q1][301] = 1;

    mas1[q2][4] = 6;
    mas2[q2][4] = 2;
    mas1[q2][16] = 'continue';
    mas2[q2][16] = 1;
    mas1[q2][31] = 3;
    mas2[q2][31] = 3;
    mas1[q2][301] = 'pop';
    mas2[q2][301] = 0;

    mas1[q3][4] = 99;
    mas1[q3][16] = 7;
    mas2[q3][16] = 3;
    mas1[q3][31] = 99;
    mas1[q3][301] = 4;
    mas2[q3][301] = 0;

    for (i = 0; i < movesLen; i++)
    {
        move = moves[i];
        if (move != 4 && move != 16 && move != 31 && move != 301)
        {
            j = 0;
            while (res[j] != 0 && j < resLen)
            {
                j++;
                n++;
            }
            return n;
        }

        active = mas1[point][move];
        switch (active)
        {
        case 'repeat':
            point = mas2[point][move];
            j = j - 1;
            break;

        case 99:
        case 'break':
            j = 0;
            while (res[j] != 0 && j < resLen)
            {
                j++;
                n++;
            }
            return n;

        case 'pop':
            if (j <= 0)
            {
                return 0;
            }
            res[j - 1] = 0;
            j--;
            point = mas2[point][move];
            break;

        case 'continue':
            point = mas2[point][move];
            break;

        default:
                res[j] = active;
                j++;
                point = mas2[point][move];
                break;
        }
    }
    j = 0;

        while (res[j] != 0 && j < resLen)
        {
            j++;
            n++;
        }

	return n;
}
void printArray(int arr[], int size) {
	int i;
	for (i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
}


int main()
{
	int moves[10] = { 4,16,31,301,4,16,31,301,301};
	int result;
	int movesLength = 10;
	int res[20] = { 0 };
	int resLength = 11;
	int i;
    result = run(moves, movesLength, res, resLength);
	printf("Vhidna : ");
	printArray(moves, movesLength);
	puts("");
	printf("Vihidna : ");
    printArray(res, resLength);
	puts("");
    printf("Result: %i\n", result);
	getchar();
    return 0;
}
