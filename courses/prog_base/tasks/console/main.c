#include <stdio.h>
#include <Windows.h>

COORD pos;
HANDLE hConsole;
int * xPoint;
int * yPoint;

void position(int coordX, int coordY)
{
	pos.X = coordX;
	pos.Y = coordY;
	SetConsoleCursorPosition(hConsole, pos);
	Sleep(3);
	printf("*");
}

void colorCons(int cordY )
{
    int color;
    if (cordY%3 == 0)
    {
        color = BACKGROUND_RED | BACKGROUND_INTENSITY;
    }
    if (cordY%3  == 1)
    {
        color = BACKGROUND_RED | BACKGROUND_GREEN| BACKGROUND_INTENSITY;
    }
    if (cordY%3 == 2)
    {
        color = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY ;
    }
    SetConsoleTextAttribute(hConsole, color);
}


void consoleMoveXR(int cordX, int cordY, int endX)      /* ---->>> */
{
	while (cordX < endX - 1)
    {
        colorCons ( cordY );
		position(cordX, cordY);
		cordX++;
		(*xPoint)++;
		(*yPoint) = cordY;

	}

}
void consoleMoveXL(int cordX, int cordY, int endX)    /*  <<<----   */
{
	while (cordX > endX)
    {
        colorCons ( cordY );
		position(cordX, cordY);
		cordX--;
		(*xPoint)--;
		(*yPoint) = cordY;

	}

}
void consoleMoveYUp(int cordX, int cordY, int endY)
{
	while (cordY > endY)
    {
        colorCons ( cordY );
		position(cordX, cordY);
		cordY--;
		(*xPoint) = cordX;
		(*yPoint)--;

	}
}
void consoleMoveYDown(int cordX, int cordY, int endY)
{
	while (cordY < endY - 1)
    {
        colorCons( cordY );
		position(cordX, cordY);
		cordY++;
		(*xPoint) = cordX;
		(*yPoint)++;

	}
}

int main(void)
{
	int cordX = 80;
	int cordY = 0;
	int xLUp = 0;
	int xRDn = 80;
	int yRUp = 0;
	int yLDn = 25;

	xPoint = &cordX;
	yPoint = &cordY;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	while (cordY != 12)
    {
		consoleMoveXL(cordX, cordY, xLUp);
		consoleMoveYDown(cordX, cordY, yLDn);
		consoleMoveXR(cordX, cordY, xRDn);
		consoleMoveYUp(cordX, cordY, yRUp);
		cordX--;
		cordY++;
		xLUp++;
		yLDn--;
		xRDn--;
		yRUp++;

	}
	consoleMoveXL(cordX, cordY, xLUp);
	position(cordX, cordY);

	getchar();
	return 0;
}
