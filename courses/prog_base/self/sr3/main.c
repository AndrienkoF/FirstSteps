#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void randMas(int n, int mas[])
{
    int i;
    for (i = 0; i < n; i++)
    {
        mas[i] = rand()%41 - 20;
    }
}

void pointMas(int *ptr, int mas[], int n )
{
    int i;
    for (i = 0; i < n; i++)
    {
        *(ptr + i) == mas[i];
    }
}

int main()
{
    int i, num = 0;
    int n = 5;
    int mas[n];
    int *ptr = &mas;

    srand(time(NULL));
    randMas( n, mas);
    puts("Random [-20 ; 20] massiv: ");
	for (i = 0; i < n; i++)
    {
		printf("%d ", mas[i]);
	}
	puts("\n");

	pointMas(ptr, mas, n );
	for (i = 0; i < n; i++)
    {
        printf("Pointer for position: %i  = %i\n", i, *(ptr + i));
    }

    return 0;
}
