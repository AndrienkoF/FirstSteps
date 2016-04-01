#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;    //объ€вили sfml объект "вид", который и €вл€етс€ камерой

View getPlayerCoordinateForView(float x,float y){    //функци€ дл€ считывани€ координат игрока

	view.setCenter(x + 100, y);                      // +100 - сместили камеру по иксу вправо.

	return view;
}

View viewmap(float time){   //функци€ дл€ перемещени€ камеры по карте. принимает врем€ sfml

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
		view.setViewport(sf::FloatRect(0, 0, 0.5f, 1));  //таким образом делаетс€ раздельный экран дл€ игры на двоих
	}   //нужно только создать ещЄ один объект View и прив€зывать к нему координаты игрока 2.

    return view;
}
