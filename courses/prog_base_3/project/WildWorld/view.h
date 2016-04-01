#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;    //объ€вили sfml объект "вид", который и €вл€етс€ камерой

View getPlayerCoordinateForView(float x,float y){    //функци€ дл€ считывани€ координат игрока
	view.setCenter(x + 100, y);                      // +100 - сместили камеру по иксу вправо.
	return view;
}

View viewMap(float time){   //функци€ дл€ перемещени€ камеры по карте. принимает врем€ sfml
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		view.move(0.1*time, 0);     //скроллим карту вправо
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		view.move(0, 0.1*time);     //скроллим карту вниз
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		view.move(-0.1*time, 0);    //скроллим карту влево
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		view.move(0, -0.1*time);    //скроллим карту вправо
	}

    return view;
}
