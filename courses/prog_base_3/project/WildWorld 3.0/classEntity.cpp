#include "classEntity.h"

Entity::Entity(sf::Image &image, sf::String Name, float X, float Y, float W, float H){
    x = X; y = Y; w = W; h = H; name = Name;
    moveTimer = 0; speed = 0; health = 100; dx = 0; dy = 0;
    life = true; onGround = false; isMove = false; info = false; crashed = false; build = false; market = false;
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setOrigin(w/2, h/2);
}
