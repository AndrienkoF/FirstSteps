#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include "level.h"
#include "classEntity.h"

using namespace sf;

class Enemy :public Entity{
public:
    float CurrentFrame;
    Enemy(Image &image, String Name, Level &lev, float X, float Y, float W, float H);
    void checkCollisionWithMap(float Dx, float Dy);
    void update(sf::View * view, float time);

};

