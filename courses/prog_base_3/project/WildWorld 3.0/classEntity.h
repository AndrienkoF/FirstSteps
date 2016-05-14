#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "level.h"
#include <vector>
#include <list>

using namespace sf;

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
