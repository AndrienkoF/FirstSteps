#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "map.h"           //карта
#include "view.h"          //вид камеры

using namespace sf;   //включаем пространство имен sf (sf::)


/////////////////////////////////////////// ОБЩИЙ КЛАСС //////////////////////////////////////////////////////////
class Entity{
public:
    float dx, dy, x, y, speed, moveTimer;
    int w, h, health;
    bool life, isMove, onGround;
    Texture texture;
    Sprite sprite;
    String name;
    Entity(Image &image, float X, float Y, float W, float H, String Name){
        x = X; y = Y; w = W; h = H; name = Name;
        moveTimer = 0; speed = 0; health = 100; dx = 0; dy = 0;
        life = true; onGround = false; isMove = false;
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setOrigin(w/2, h/2);
    }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////// КЛАСС ИГРОКА /////////////////////////////////////////////////////////
class Player: public Entity{
public:
    enum{left, right, up, down, jump, stay}state;
    int playerScore;

    Player (Image &image, float X, float Y, float W, float H, String Name) :Entity(image, X, Y, W, H, Name){
        playerScore = 0;
        state = stay;
        if(name == "Hero"){
            sprite.setTextureRect(IntRect(0,0,w,h));
        }
    }

    void control(){
        if (Keyboard::isKeyPressed){
            if (Keyboard::isKeyPressed(Keyboard::Left)){
                state = left;
                speed = 0.1;
            }
            if (Keyboard::isKeyPressed(Keyboard::Right)){
                state = right;
                speed = 0.1;
            }
            if ((Keyboard::isKeyPressed(Keyboard::Up))&& (onGround)){
                state = jump;
                dy = -0.6;
                onGround = false;
            }
            if (Keyboard::isKeyPressed(Keyboard::Down)){
                state = down;
            }
        }
    }

    void checkCollisionWithMap(float Dx, float Dy){   //функция проверки столкновений с картой
        for (int i = y / 32; i < (y + h) / 32; i++)   //проходимся по элементам карты
		for (int j = x / 32; j < (x + w) / 32; j++){
			if ((TileMap[i][j] == '0') || (TileMap[i][j] == '1')){
				if (Dy>0){ y = i * 32 - h;  dy = 0; onGround = true; }
				if (Dy<0){y = i * 32 + 32;  dy = 0;}
				if (Dx>0){x = j * 32 - w;}
				if (Dx<0){x = j * 32 + 32;}
			}
		}
	}

    void update(float time){  //функция для движения
        control();
        switch(state){
            case right: dx = speed; break;
            case left: dx = -speed; break;
            case up: break;
            case down: dx = 0; break;
            case stay: dx = 0; break;
		}
		x += dx*time;
		checkCollisionWithMap(dx, 0);   //столкновение по Х

		y += dy*time;
		checkCollisionWithMap(0, dy);   //столкновение по Y

        sprite.setPosition(x + w/2, y + h/2);
        if(health <= 0){
            life = false;
        }
        if(!isMove){
            speed = 0;
        }
        if(life){
            setPlayerCoordinateForView(x, y);
        }
        dy = dy + 0.0015*time;   //постоянно притягиваемся к земле
    }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////// КЛАСС ВРАГА ////////////////////////////////////////////////////////////
class Enemy :public Entity{
public:
    Enemy(Image &image, float X, float Y, float W, float H, String Name) :Entity(image, X, Y, W, H, Name){
        if(name == "EasyEnemy1"){
            sprite.setTextureRect(IntRect(0,0,w,h));
            dx = 0.1;
        }
    }

    void checkCollisionWithMap(float Dx, float Dy){   //функция проверки столкновений с картой
        for (int i = y / 32; i < (y + h) / 32; i++)   //проходимся по элементам карты
		for (int j = x / 32; j < (x + w) / 32; j++){
			if ((TileMap[i][j] == '0') || (TileMap[i][j] == '1')){
				if (Dy>0){ y = i * 32 - h;}
				if (Dy<0){y = i * 32 + 32;}
				if (Dx>0){x = j * 32 - w; dx = -0.1; sprite.scale(-1,1);}
				if (Dx<0){x = j * 32 + 32; dx = 0.1; sprite.scale(-1,1);}
			}
		}
	}

    void update(float time){
        if(name == "EasyEnemy1"){
            // moveTimer += time;
            // if(moveTimer>3000){dx *= -1; moveTimer = 0;}  // для изменения направление каждые 3 секунды
            checkCollisionWithMap(dx, 0);
            x += dx*time;
            sprite.setPosition(x + w/2, y + h/2);
            if(health <= 0){
                life = false;
            }
        }
    }

};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){
	RenderWindow window(VideoMode(640, 480), "WildWorld");
    view.reset(sf::FloatRect(0, 0, 640, 480));              //размер "вида" камеры

    Image map_image;                                        //объект изображения для карты
	map_image.loadFromFile("images/map.png");               //загружаем файл для карты
	Texture map;
	map.loadFromImage(map_image);                           //заряжаем текстуру картинкой
	Sprite s_map;
	s_map.setTexture(map);                                  //заливаем текстуру спрайтом

    Image heroImage;
    heroImage.loadFromFile("images/Hero.png");

    Image easyEnemy1Image;
    easyEnemy1Image.loadFromFile("images/Goat.png");

    Player hero(heroImage, 100, 100, 37, 50, "Hero");
    Enemy easyEnemy1(easyEnemy1Image, 595, 691, 46, 45, "EasyEnemy1");

    Clock clock;    //создаем переменную времени, привязка ко времени(а не загруженности/мощности процессора).
    while (window.isOpen()){
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();     //перезагружает время
        time = time / 800;   //скорость игры

		Event event;
		while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
            window.close();
        }

        hero.update(time);
        easyEnemy1.update(time);

        window.setView(view);
		window.clear();

		////////////////////////////////  РИСУЕМ КАРТУ  //////////////////////////////////////////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++){
			if (TileMap[i][j] == ' ') s_map.setTextureRect(IntRect(0, 0, 32, 32));
			if (TileMap[i][j] == 's') s_map.setTextureRect(IntRect(32, 0, 32, 32));
			if (TileMap[i][j] == '0') s_map.setTextureRect(IntRect(64, 0, 32, 32));
			if (TileMap[i][j] == 'f') s_map.setTextureRect(IntRect(96, 0, 32, 32));
			if (TileMap[i][j] == 'h') s_map.setTextureRect(IntRect(128, 0, 32, 32));
			if (TileMap[i][j] == '1') s_map.setTextureRect(IntRect(160, 0, 32, 32));
            if (TileMap[i][j] == '2') s_map.setTextureRect(IntRect(192, 0, 32, 32));


			s_map.setPosition(j * 32, i * 32);    //задает каждому из них позицию
			window.draw(s_map);                   //рисуем квадратики на экран
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////

        window.draw(easyEnemy1.sprite);
		window.draw(hero.sprite);     //выводим спрайт на экран
		window.display();
	}
	return 0;
}
