#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
//#include "map.h"           //карта
#include "view.h"          //вид камеры
#include "level.h"
#include <vector>
//#include <list>


using namespace sf;   //включаем пространство имен sf (sf::)


/////////////////////////////////////////// ОБЩИЙ КЛАСС //////////////////////////////////////////////////////////
class Entity{
public:
    std::vector<Object>obj;   //вектор объектов карты
    float dx, dy, x, y, speed, moveTimer;
    int w, h, health;
    bool life, isMove, onGround;
    Texture texture;
    Sprite sprite;
    String name;
    Entity(Image &image, String Name, float X, float Y, float W, float H){
        x = X; y = Y; w = W; h = H; name = Name;
        moveTimer = 0; speed = 0; health = 100; dx = 0; dy = 0;
        life = true; onGround = false; isMove = false;
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setOrigin(w/2, h/2);
    }

    FloatRect getRect(){    //функция получения прямоугольника, его координат и размер
        return FloatRect(x, y, w, h);    //для проверки столкновения
    }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////// КЛАСС ИГРОКА /////////////////////////////////////////////////////////
class Player: public Entity{
public:
    enum{left, right, up, down, jump, stay}state;
    int playerScore;

    Player (Image &image, String Name, Level &lev, float X, float Y, float W, float H) :Entity(image, Name, X, Y, W, H){
        playerScore = 0;
        state = stay;
        obj = lev.GetAllObjects();   //получаем все объкты с карты
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
		for (int i = 0; i < obj.size(); i++)   //проходимся по объектам
		if (getRect().intersects(obj[i].rect)){   //проверка пересечения игрока с объктом
			if (obj[i].name == "solid"){
				if (Dy>0){y = obj[i].rect.top - h;  dy = 0; onGround = true; }
				if (Dy<0){y = obj[i].rect.top + obj[i].rect.height;  dy = 0;}
				if (Dx>0){x = obj[i].rect.left - w;}
				if (Dx<0){x = obj[i].rect.left + obj[i].rect.width;}
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
    Enemy(Image &image, String Name, Level &lev, float X, float Y, float W, float H) :Entity(image, Name, X, Y, W, H){
        obj = lev.GetObjects("solid");
        if(name == "EasyEnemy1"){
            sprite.setTextureRect(IntRect(0,0,w,h));
            dx = 0.1;
        }
    }

    void checkCollisionWithMap(float Dx, float Dy){   //функция проверки столкновений с картой
		for (int i = 0; i < obj.size(); i++)   //проходимся по объектам
		if (getRect().intersects(obj[i].rect)){   //проверка пересечения игрока с объктом
            if (Dy>0){y = obj[i].rect.top - h;  dy = 0; onGround = true; }
            if (Dy<0){y = obj[i].rect.top + obj[i].rect.height;  dy = 0;}
            if (Dx>0){x = obj[i].rect.left - w; dx = -0.1; sprite.scale(-1,1);}
            if (Dx<0){x = obj[i].rect.left + obj[i].rect.width; dx = 0.1; sprite.scale(-1,1);}
		}
	}

    void update(float time){
        if(name == "EasyEnemy1"){
            // moveTimer += time;
            // if(moveTimer>3000){dx *= -1; moveTimer = 0;}  // для изменения направление каждые 3 секунды
            x += dx*time;
            checkCollisionWithMap(dx, 0);
            y += dy*time;
            checkCollisionWithMap(0, dy);
            sprite.setPosition(x + w/2, y + h/2);
            if(health <= 0){
                life = false;
            }
            dy = dy + 0.0015*time;   //постоянно притягиваемся к земле
        }
    }

};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){
	RenderWindow window(VideoMode(640, 480), "WildWorld");
    view.reset(sf::FloatRect(0, 0, 640, 480));              //размер "вида" камеры

    Level lvl;  //создали экземпляр класса уровень
    lvl.LoadFromFile("map.tmx");

    Image heroImage;
    heroImage.loadFromFile("images/Hero.png");

    Image easyEnemy1Image;
    easyEnemy1Image.loadFromFile("images/Goat.png");

    Object player = lvl.GetObject("player");
    Object easyEnemyObject = lvl.GetObject("easyEnemy");

    Player hero(heroImage, "Hero", lvl, player.rect.left, player.rect.top, 37, 50);
    Enemy easyEnemy1(easyEnemy1Image, "EasyEnemy1", lvl, easyEnemyObject.rect.left, easyEnemyObject.rect.top, 46, 45);

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

		lvl.Draw(window); //рисуем карту

        window.draw(easyEnemy1.sprite);
		window.draw(hero.sprite);     //выводим спрайт на экран
		window.display();
	}
	return 0;
}
