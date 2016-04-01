#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;    //объявили sfml объект "вид", который и является камерой

View getPlayerCoordinateForView(float x,float y){    //функция для считывания координат игрока

	float tempX = x; float tempY = y;   //считываем коорд игрока и проверяем их, чтобы убрать края

	if (x < 320) tempX = 320;    //убираем из вида левую сторону
	if (y < 240) tempY = 240;    //верхнюю сторону
	if (y > 554) tempY = 554;    //нижнюю сторону

	view.setCenter(tempX, tempY);       //следим за игроком, передавая его координаты.

	return view;
}

View viewmap(float time){   //функция для перемещения камеры по карте. принимает время sfml

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

View changeview(){

	if (Keyboard::isKeyPressed(Keyboard::U)) {
		view.zoom(1.0100f);      //масштабируем, уменьшение
	}

	if (Keyboard::isKeyPressed(Keyboard::R)) {
		//view.setRotation(90);  //сразу же задает поворот камере
		view.rotate(1);          //постепенно поворачивает камеру (отрицательное значение - в обратную сторону)
	}


	if (Keyboard::isKeyPressed(Keyboard::I)) {
		view.setSize(640, 480);  //устанавливает размер камеры (исходный)
	}

	if (Keyboard::isKeyPressed(Keyboard::P)) {
		view.setSize(540, 380);  //например другой размер
	}


	if (Keyboard::isKeyPressed(Keyboard::Q)) {
		view.setViewport(sf::FloatRect(0, 0, 0.5f, 1));  //таким образом делается раздельный экран для игры на двоих
	}   //нужно только создать ещё один объект View и привязывать к нему координаты игрока 2.

    return view;
}
