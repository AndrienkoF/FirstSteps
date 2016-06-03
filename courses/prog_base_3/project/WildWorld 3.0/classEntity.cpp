#include "classEntity.h"

Entity::Entity(Image &image, String Name, float X, float Y, float W, float H){
    x = X; y = Y; w = W; h = H; name = Name;
    moveTimer = 0; speed = 0; health = 100; dx = 0; dy = 0;
    life = true; onGround = false; isMove = false; info = false; build = false;
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setOrigin(w/2, h/2);
}
