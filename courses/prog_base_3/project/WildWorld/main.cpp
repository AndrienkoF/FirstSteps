#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"      //подключили код с картой
#include "view.h"     //подключили код с видом камеры

using namespace sf;  //включаем пространство имен sf, чтобы постоянно не писать sf::

/////////////////////////////////////////// КЛАСС ИГРОКА /////////////////////////////////////////////////////////

class Player {

private: float x, y = 0;             //объявили переменные, в конструкторе Player ниже дадим им значения
public:
	float w, h, dx, dy, speed;   // dx dy speed будут = 0 в конструкторе класса ниже
    int dir;                     //направление (движения) игрока
    String File;
    Image image;                 //изображение
    Texture texture;             //текстура
    Sprite sprite;               //спрайт

    Player (String F, float X, float Y, float W, float H){
        File = F;
        float w = W;
        float h = H;
        image.loadFromFile("images/" + File);      //запихиваем наше изображение
        //image.createMaskFromColor(Color( , , )); //можно убрать ненунжный цвет !!!
        texture.loadFromImage(image);              //закидываем изображение в текстуру
        sprite.setTexture(texture);                //заливаем спрайт текстурой
        x = X, y = Y;                              //координаты появления спрайта
        sprite.setTextureRect(IntRect(0,0,w,h));   //задаем спрайту прямоугольник
    }

    void update(float time){ //функция для движения
        switch(dir){
        case 0:
            dx = speed;
            dy = 0;
            break;
        case 1:
            dx = -speed;
            dy = 0;
            break;
        case 2:
            dx = 0;
            dy = speed;
            break;
        case 3:
            dx = 0;
            dy = -speed;
            break;
        }

        x += dx*time;
        y += dy*time;

        speed = 0;
        sprite.setPosition(x,y);
    }

    float getPlayerCoordinateX(){	//этим методом будем забирать координату Х
        return x;
    }
    float getPlayerCoordinateY(){	//этим методом будем забирать координату Y
        return y;
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){
	RenderWindow window(VideoMode(640, 480), "WildWorld");  //увеличили для удобства размер окна
    view.reset(sf::FloatRect(0, 0, 640, 480));              //размер "вида" камеры

    Image map_image;                                        //объект изображения для карты
	map_image.loadFromFile("images/map.png");               //загружаем файл для карты
	Texture map;                                            //текстура карты
	map.loadFromImage(map_image);                           //заряжаем текстуру картинкой
	Sprite s_map;                                           //создаём спрайт для карты
	s_map.setTexture(map);                                  //заливаем текстуру спрайтом

    Player hero("allHero.png", 250, 250, 48, 56);

    float CurrentFrame = 2;
    Clock clock; //создаем переменную времени, привязка ко времени(а не загруженности/мощности процессора).

	while (window.isOpen()){

	    float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
        clock.restart();                                      //перезагружает время
        time = time/800;                                      //скорость игры
		//std::cout << time << "\n";                          //смотрим как живет время (перезагружается, как видим)

		Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}

        ///////////////////////////////// УПРАВЛЕНИЕ ПЕРСОНАЖЕМ "HERO" //////////////////////////////////////////////////
		if ((Keyboard::isKeyPressed(Keyboard::Right))){ //если нажата клавиша стрелка влево или англ буква А
			hero.dir = 0;
			hero.speed = 0.1;
			CurrentFrame += 0.005*time;                 //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (CurrentFrame > 5) CurrentFrame -= 3;    // если пришли к третьему кадру - откидываемся назад.
			hero.sprite.setTextureRect(IntRect(46 *int(CurrentFrame), 0, 46, 56));
            getPlayerCoordinateForView(hero.getPlayerCoordinateX(), hero.getPlayerCoordinateY());   //передаем координаты игрока в функцию управления камерой
		}
		if ((Keyboard::isKeyPressed(Keyboard::Left))){  //если нажата клавиша стрелка влево или англ буква А
			hero.dir = 1;
			hero.speed = 0.1;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 5) CurrentFrame -= 2;
			hero.sprite.setTextureRect(IntRect(46 *int(CurrentFrame), 0, -46, 56));
			getPlayerCoordinateForView(hero.getPlayerCoordinateX(), hero.getPlayerCoordinateY());   //передаем координаты игрока в функцию управления камерой
		}
        if ((Keyboard::isKeyPressed(Keyboard::Up))){
                hero.dir = 3;
                hero.speed = 0.1;
                hero.sprite.setTextureRect(IntRect(144, 112, 48, 56));
                getPlayerCoordinateForView(hero.getPlayerCoordinateX(), hero.getPlayerCoordinateY());   //передаем координаты игрока в функцию управления камерой
        }
        if ((Keyboard::isKeyPressed(Keyboard::Down))){
                hero.dir = 2;
                hero.speed = 0.1;
                hero.sprite.setTextureRect(IntRect(92, 112, 48, 56));
                getPlayerCoordinateForView(hero.getPlayerCoordinateX(), hero.getPlayerCoordinateY());   //передаем координаты игрока в функцию управления камерой
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////

        hero.update(time);
        window.setView(view);     //"оживляем" камеру в окне sfml
		window.clear();

		/////////////////////////////////////////////  РИСУЕМ КАРТУ  /////////////////////////////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++){
			if (TileMap[i][j] == ' ')   s_map.setTextureRect(IntRect(0, 0, 32, 32));  //если встретили символ пробел, то рисуем 1й квадратик
			if (TileMap[i][j] == 's')   s_map.setTextureRect(IntRect(32, 0, 32, 32)); //если встретили символ s, то рисуем 2й квадратик
			if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32)); //если встретили символ 0, то рисуем 3й квадратик

			s_map.setPosition(j * 32, i * 32);    //задает каждому из них позицию
			window.draw(s_map);                   //рисуем квадратики на экран
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////

		window.draw(hero.sprite);     //выводим спрайт на экран
		window.display();
	}

	return 0;
}
