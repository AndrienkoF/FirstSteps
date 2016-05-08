#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "view.h"          //вид камеры
#include "level.h"
#include <vector>
#include <list>


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

    virtual void update (float time) = 0;  //все потомки переопределяют эту функцию
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
		for (int i = 0; i < obj.size(); i++)          //проходимся по объектам
		if (getRect().intersects(obj[i].rect)){       //проверка пересечения игрока с объктом
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

    ////////////////////////// ШРИФТ //////////////////////////////////////////////////////////////////////////////
    Font font;
    font.loadFromFile("font/Belepotan.ttf");   //файл шрифта
    Text text("", font, 20);
    text.setColor(Color::Black);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Level lvl;  //создали экземпляр класса уровень
    lvl.LoadFromFile("map.tmx");

    Image heroImage;
    heroImage.loadFromFile("images/Hero.png");

    Image easyEnemy1Image;
    easyEnemy1Image.loadFromFile("images/Goat.png");

    std::list<Entity*> entities;       //создаем список
    std::list<Entity*>::iterator it;   //итератор, чтобы проходить по элементам списка
    std::list<Entity*>::iterator it2;

    std::vector<Object> e = lvl.GetObjects("easyEnemy");
    for (int i = 0; i < e.size(); i++){
        entities.push_back(new Enemy(easyEnemy1Image, "EasyEnemy1", lvl, e[i].rect.left, e[i].rect.top, 46, 45));
    }

    Object player = lvl.GetObject("player");
    Player hero(heroImage, "Hero", lvl, player.rect.left, player.rect.top, 37, 50);

    float moveTimer = 0;

    Clock clock;    //создаем переменную времени, привязка ко времени(а не загруженности/мощности процессора).
    while (window.isOpen()){
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();     //перезагружает время
        time = time / 800;   //скорость игры
        moveTimer += time;

		Event event;
		while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
            window.close();
        }

        hero.update(time);
        for (it = entities.begin(); it != entities.end();){
            Entity *b = *it;
            b->update(time);
            if (b->life == false){
                it = entities.erase(it);
                delete b;
            }else{
                it++;
            }
        }

        for (it = entities.begin(); it != entities.end(); it++){
            if ((*it)->getRect().intersects(hero.getRect())){   //если объект пересекается с игроком
                if ((*it)->name == "EasyEnemy1"){
                    if (/*(hero.dy > 0)&&(hero.onGround == false)&&*/(Keyboard::isKeyPressed(Keyboard::A))){
                        (*it)->dx = 0;
                        (*it)->health = 0;
                    }else{
                        if(moveTimer>2000){
                            hero.health -= 10;
                            moveTimer = 0;
                        }
                    }
                }
            }
        }

        for (it = entities.begin(); it != entities.end(); it++){
            for (it2 = entities.begin(); it2 != entities.end(); it2++){
                if ((*it)->getRect() != (*it2)->getRect()){   //если разные прямоугольники
                    if (((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->name == "EasyEnemy1") && ((*it2)->name == "EasyEnemy1")){  //если столкнутся два врага
                        (*it)->dx *= -1;
                        (*it)->sprite.scale(-1,1);
                    }
                }
            }
        }

        window.setView(view);
		window.clear();
		lvl.Draw(window); //рисуем карту

        std::ostringstream playerHealthString;
		playerHealthString << hero.health;
		text.setString("Helth: " + playerHealthString.str());
		text.setPosition(view.getCenter().x + 125, view.getCenter().y - 240);
		window.draw(text);

        for (it = entities.begin(); it != entities.end(); it++){
            window.draw((*it)->sprite);
        }
		window.draw(hero.sprite);     //выводим спрайт на экран
		window.display();
	}
	return 0;
}
