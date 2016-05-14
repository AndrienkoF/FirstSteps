#include <SFML/Graphics.hpp>

using namespace sf;

sf::View view;    //объ€вили sfml объект "вид", который и €вл€етс€ камерой

View setPlayerCoordinateForView(float x,float y){    //функци€ дл€ считывани€ координат игрока

	float tempX = x; float tempY = y;   //считываем коорд игрока и провер€ем их, чтобы убрать кра€
    //printf("%f  %f\n", tempX, tempY);
	if (x < 600) tempX = 600;    //убираем из вида левую сторону
	if (y < 400) tempY = 400;    //верхнюю сторону
	if (x > 1600) tempX = 1600;  //правую сторону
    if (y > 550) tempY = 550;    //нижн€€ сторона


	view.setCenter(tempX, tempY);       //следим за игроком, передава€ его координаты.
	return view;
}
