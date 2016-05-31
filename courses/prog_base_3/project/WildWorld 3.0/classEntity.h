#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "level.h"
#include <vector>
#include <list>

using namespace sf;

class Entity{
public:
    std::vector<Object>obj;   //вектор объектов карты
    float dx, dy, x, y, speed, moveTimer;
    int w, h, health;
    bool life, isMove, onGround;
    Texture texture;
    Sprite sprite;
    String name;

    Entity(Image &image, String Name, float X, float Y, float W, float H);

    FloatRect getRect(){                  //функци€ получени€ пр€моугольника, его координат и размер
        return FloatRect(x, y, w, h);    //дл€ проверки столкновени€
    }

    virtual void update (sf::View * view, float time) = 0;  //все потомки переопредел€ют эту функцию
};
