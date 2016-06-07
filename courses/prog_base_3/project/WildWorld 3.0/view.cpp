#include "view.h"

void setPlayerCoordinateForView(sf::View * view, float x,float y){    //функция для считывания координат игрока
	float tempX = x; float tempY = y;   //считываем коорд игрока и проверяем их, чтобы убрать края
	if (x < 600) tempX = 600;    //убираем из вида левую сторону
	if (y < 400) tempY = 400;    //верхнюю сторону
	if (x > 5800) tempX = 5800;  //правую сторону
    if (y > 550) tempY = 550;    //нижняя сторона

	view->setCenter(tempX, tempY);       //следим за игроком, передавая его координаты.
}
