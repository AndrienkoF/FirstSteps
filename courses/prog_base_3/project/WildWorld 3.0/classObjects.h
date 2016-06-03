#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "level.h"
#include <vector>
#include <list>
#include "classEntity.h"

//using namespace sf;

class Objects:public Entity{
public:
    Objects(sf::Image &image, sf::String Name, Level &lev, float X, float Y, float W, float H);
    void checkCollisionWithMap(float Dx, float Dy);
    void update(sf::View * view, float time);
};
