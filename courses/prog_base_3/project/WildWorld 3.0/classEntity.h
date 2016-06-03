#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "level.h"
#include <vector>
#include <list>

//using namespace sf;

class Entity{
public:
    std::vector<Object>obj;   //������ �������� �����
    float dx, dy, x, y, speed, moveTimer;
    int w, h, health;
    bool life, isMove, onGround, info, build;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::String name;

    Entity(sf::Image &image, sf::String Name, float X, float Y, float W, float H);

    sf::FloatRect getRect(){                  //������� ��������� ��������������, ��� ��������� � ������
        return sf::FloatRect(x, y, w, h);    //��� �������� ������������
    }

    virtual void update (sf::View * view, float time) = 0;  //��� ������� �������������� ��� �������
};
