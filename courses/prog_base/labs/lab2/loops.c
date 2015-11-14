#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calc(int n, int m)
{
    int i, j;
    double res = 0;
    double temp = 0;


    for (i = 1; i < n; i++)
    {
        for (j = 1; j < m; j++)
        {
            temp += 2 + 1 / (j + 2);
        }

        res += i*temp;
        temp = 0;
    }

    return res;
}

int main(void)
{

    double res;
    int n = 7;
    int m = 3;
    printf("%f\n", calc(n, m));

    return 0;
}
