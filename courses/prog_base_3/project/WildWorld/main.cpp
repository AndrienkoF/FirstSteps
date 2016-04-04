#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "map.h"      //карта
#include "view.h"     //вид камеры

using namespace sf;   //включаем пространство имен sf (sf::)

/////////////////////////////////////////// КЛАСС ИГРОКА /////////////////////////////////////////////////////////

class Player {

private: float x, y = 0;
public:
	float w, h, dx, dy, speed;
    int dir;                     //направление (движения) игрока
    int playerScore;
    String File;
    Image image;
    Texture texture;
    Sprite sprite;

    Player (String F, float X, float Y, float W, float H){
        dir = 0; speed = 0; playerScore = 0;
        File = F;
        float w = W;
        float h = H;
        image.loadFromFile("images/" + File);
        //image.createMaskFromColor(Color( , , )); //можно убрать ненунжный цвет !!!
        texture.loadFromImage(image);              //закидываем изображение в текстуру
        sprite.setTexture(texture);                //заливаем спрайт текстурой
        x = X, y = Y;                              //координаты появления спрайта
        sprite.setTextureRect(IntRect(0,0,w,h));   //задаем спрайту прямоугольник
    }

    void update(float time){  //функция для движения
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
		interactionWithMap();
    }

    float getPlayerCoordinateX(){
        return x;
    }
    float getPlayerCoordinateY(){
        return y;
    }

    void interactionWithMap(){   //функция взаимодействия с картой
        for (int i = y / 32; i < (y + h) / 32; i++)
        for (int j = x / 32; j < (x + w) / 32; j++){
            if (TileMap[i][j] == '0'){
                if (dy > 0){
                    y = i * 32 - h;
                }
                if (dy < 0){
                    y = i * 32 + 32;
                }
                if (dx > 0){
                    x = j * 32 - w;
                }
                if (dx < 0){
                    x = j * 32 + 32;
                }
            }
            if (TileMap[i][j] == 's') {
				playerScore++;
				TileMap[i][j] = ' ';
			}
        }
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){
	RenderWindow window(VideoMode(640, 480), "WildWorld");
    view.reset(sf::FloatRect(0, 0, 640, 480));              //размер "вида" камеры

    ////////////////////////// ШРИФТ //////////////////////////////////////////////////////////////////////////////
    Font font;
    font.loadFromFile("font/CyrilicOld.ttf");   //файл шрифта
    Text text("", font, 20);
    text.setColor(Color::Green);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);   //жирный и подчеркнутый текст
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Image map_image;                                        //объект изображения для карты
	map_image.loadFromFile("images/map.png");               //загружаем файл для карты
	Texture map;
	map.loadFromImage(map_image);                           //заряжаем текстуру картинкой
	Sprite s_map;
	s_map.setTexture(map);                                  //заливаем текстуру спрайтом

    Player hero("Hero.png", 250, 250, 37, 55);

    float CurrentFrame = 2;
    Clock clock;    //создаем переменную времени, привязка ко времени(а не загруженности/мощности процессора).

	while (window.isOpen()){

	    float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
        clock.restart();                                      //перезагружает время
        time = time/800;                                      //скорость игры
		//std::cout << time << "\n";                          //время

		Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}

        ///////////////////////////////// УПРАВЛЕНИЕ ПЕРСОНАЖЕМ "HERO" //////////////////////////////////////////////////
		if (Keyboard::isKeyPressed(Keyboard::Right)){
			hero.dir = 0;
			hero.speed = 0.1;
			CurrentFrame += 0.005*time;                 //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (CurrentFrame > 3) CurrentFrame -= 3;
			hero.sprite.setTextureRect(IntRect(37 *int(CurrentFrame), 0, 37, 55));
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)){
			hero.dir = 1;
			hero.speed = 0.1;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 4) CurrentFrame -= 3;
			hero.sprite.setTextureRect(IntRect(37 *int(CurrentFrame), 61, 37, 55));
		}
        if (Keyboard::isKeyPressed(Keyboard::Up)){
                hero.dir = 3;
                hero.speed = 0.1;
                if (CurrentFrame > 3) CurrentFrame -= 3;
                hero.sprite.setTextureRect(IntRect(37 *int(CurrentFrame), 0, 37, 55));
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)){
                hero.dir = 2;
                hero.speed = 0.1;
                CurrentFrame += 0.005*time;
                if (CurrentFrame > 4) CurrentFrame -= 3;
                hero.sprite.setTextureRect(IntRect(37 *int(CurrentFrame), 61, 37, 55));
        }

        getPlayerCoordinateForView(hero.getPlayerCoordinateX(), hero.getPlayerCoordinateY());   //передаем координаты игрока в функцию управления камерой
        hero.update(time);
        window.setView(view);     //"оживляем" камеру в окне sfml
		window.clear();

		/////////////////////////////////////////////  РИСУЕМ КАРТУ  /////////////////////////////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++){
			if (TileMap[i][j] == ' ')   s_map.setTextureRect(IntRect(0, 0, 32, 32));
			if (TileMap[i][j] == 's')   s_map.setTextureRect(IntRect(32, 0, 32, 32));
			if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));

			s_map.setPosition(j * 32, i * 32);    //задает каждому из них позицию
			window.draw(s_map);                   //рисуем квадратики на экран
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::ostringstream playerScoreString;
		playerScoreString << hero.playerScore;		                            //занесли в нее число очков
		text.setString("Stones:" + playerScoreString.str());                    //методом .str() вызываем сформированную строку
		text.setPosition(view.getCenter().x - 310, view.getCenter().y - 240);   //задаем позицию текста, отступая от центра камеры
		window.draw(text);

		window.draw(hero.sprite);     //выводим спрайт на экран
		window.display();
	}

	return 0;
}
