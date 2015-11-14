#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void fillRand2(int arr[], int size)
{
  int i;
  for ( i = 0; i < size; i++)
  {
      arr[i] = rand() % 256 - 255;
  }
}

int checkRand2(int arr[], int size)
{
    int i;
    int rand = 1;
	for (i = 0; i < size; i++)
	{
		if (arr[i] > 255 || arr[i] < - 255)
        {
            rand = 0;
        }
	}
    return rand;
}

float meanValue(int arr[], int size)
{
    int i;
    float res = 0;
    for ( i = 0; i < size; i++ )
    {
        res += arr[i] /  size;
    }
    return res;

}

int minValue(int arr[], int size)
{
    int i;
    int min = arr[0];
    for ( i = 0; i < size; i++ )
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    return min;
}

int meanIndex(int arr[], int size)
{
  int i, index = 0;
	float min, minTemp;
	float mean = meanValue(arr, size);
	min = abs(arr[0] - mean);

	for (i = 0; i < size; i++)
    {
		minTemp = abs(arr[i] - mean);
		if (minTemp < min)
		{
			index = i;
			min = minTemp;
		}
	}
	return index;
}

int minIndex(int arr[], int size)
{
  int i ;
  int index = 0;
  int min = arr[0];
	for (i = size - 1; i >= 0; i--)
    {
		if (arr[i] < min)
		{
			min = arr[i];
			index = i;
		}
	}
	return index;
}

int maxOccurance(int arr[], int size)
{
    int x = 1;
    int temp ;
    int res = arr[0];
	int i, j;
	for (i = 0; i < (size - 1); i++)
    {
        int temp = 0 ;
		for (j = 1; j < size; j++)
		{
			if (arr[i] == arr[j])
            {
				temp++;
			}
		}
		if (temp > x)
        {
			res = arr[i];
			x = temp;
		}
	}
	return res;
}

int diff(int arr1[], int arr2[], int res[], int size)
{
    int i, j;
    for ( i = 0; i < size; i++)
    {
        int a = arr1[i] - arr2[i];
        res[i] = a;

        if (a != 0)
        {
            return 0;
        }
    }
    return 1;
}

void sub(int arr1[], int arr2[], int res[], int size)
{
    int i;
    for ( i = 0; i < size; i++)
    {
        res[i] = arr1[i] - arr2[i];
    }
}

int lt(int arr1[], int arr2[], int size)
{
    int i;
	for (i = 0; i < size; i++)
    {
        if ( arr1[i] < arr2[i])
        {
            return 1;
        }

        return 0;

    }

}


void lxor(int arr1[], int arr2[], int res[], int size)
{
    int i;
	for (i = 0; i < size; i++)
    {
        res[i] = arr1[i] ^ arr2[i];
    }
}

int main ()
{
    srand(time(NULL));
    int size = 6;
    int arr[size];
    int arr1[size];
	int arr2[size];
	int res[size];
	int i;
	int rand;
	fillRand2(arr,size);
	puts("Random [-255..255] array is:");
	for (i = 0; i < size; i++)
    {
		printf("%d ", arr[i]);
	}
	puts("\n");

    puts("Check:");
	rand = checkRand2(arr, size);
	printf("%d", rand);
	puts("\n");

	puts("Average value is: ");
	printf("%f", meanValue(arr, size));
	puts("\n");

    puts("Minimum element is: ");
	printf("%d", minValue( arr, size));
	puts("\n");

    puts("MeanIndex is: ");
    printf("%d", meanIndex(arr, size));
	puts("\n");

	puts("MinIndex is:");
	printf("%d", minIndex( arr, size));
	puts("\n");

	puts("MaxOccurance is:");
	printf("%d", maxOccurance( arr, size) );
	puts("\n");

    puts("NEW Random [-255..255] arrays is:");
	fillRand2(arr1, size);
	printf("Arr1: ");
	for (i = 0; i < size; i++)
    {
		printf(" %4.d ", arr1[i]);
	}
	puts("");

    fillRand2(arr2, size);
	printf("Arr2: ");
	for (i = 0; i < size; i++)
    {
		printf(" %4.d ", arr2[i]);
	}
	puts("\n");

	puts("Diff is:");
	printf("%d", diff( arr1, arr2, res, size));
	puts("\n");

	puts("Res = Arr1 - Arr2: ");
	sub(arr1, arr2, res, 12);
	for (i = 0; i < size; i++)
    {
       printf("%d ", res[i]);
    }
    puts("\n");

    puts("Arr1 less than Arr2 ?");
    printf("%d", lt( arr1, arr2, size));
    puts("\n");

    puts("Logical XOR is:");
    lxor(arr1,arr2, res, size);
    for (i = 0; i < size; i++)
    {
       printf("%d ", res[i]);
    }
	puts("\n");

    /*XOR operation*/
	/*int t = 3^5;
	printf("%d", t);
	return 0;*/
}
