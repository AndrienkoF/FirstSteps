#include <stdio.h>
#include <stdlib.h>

void fillRand(int mat[4][4])
{
    int i, j, n = 4;
    for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
    {
       mat[i][j] = rand()% 1999 - 999 ;
    }
}


void rotateCW180(int mat[4][4])
{
    int i, j, n = 4;
	int result [4][4] ;

        for (i = 0; i < n; i++){
	    for (j = 0; j < n; j++)
		{
           result [i][j] = mat[3 - i][3 - j] ;
		}
        }
        myMat(result,mat);
}

void flipH(int mat[4][4])
{
    int i, j, n = 4;
	int result[4][4] ;

		for (i = 0; i < n; i++){
		for (j = 0; j < n; j++)
		{
          result [i][j] =  mat[i][3 - j];
		}
		}
        myMat(result,mat);
}

void transposSide(int mat[4][4])
{
    int i, j, n = 4;
	int result[4][4] ;

		for (i = 0; i < n; i++){
		for (j = 0; j < n; j++)
		{
          result [i][j] = mat[3 - j][3 - i];
		}
		}
		myMat(result,mat);
}

void myMat (int Mat1[4][4], int Mat2[4][4] )
{
    int i, j, n = 4;
	for (i = 0; i < n; i++)
    {
		for (j = 0; j < n; j++)
		{
			Mat2[i][j] = Mat1[i][j];
		}
	}
}
