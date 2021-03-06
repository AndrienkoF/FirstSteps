#include "classObjects.h"

Objects::Objects(sf::Image &image, sf::String Name, Level &lev, float X, float Y, float W, float H) :Entity(image, Name, X, Y, W, H){
    obj = lev.GetAllObjects();
    if(name == "Metal"){
        sprite.setTextureRect(sf::IntRect(0,0,w,h));
    }
    if(name == "Gold"){
        sprite.setTextureRect(sf::IntRect(0,0,w,h));
    }
    if(name == "Market"){
        sprite.setTextureRect(sf::IntRect(0,0,w,h));
    }
    if(name == "Berry"){
        sprite.setTextureRect(sf::IntRect(0,0,w,h));
    }
    if(name == "Solid"){
        sprite.setTextureRect(sf::IntRect(64,0,w,h));
    }
    if(name == "Info"){
        sprite.setTextureRect(sf::IntRect(0,0,w,h));
    }
    if(name == "Ground"){
        sprite.setTextureRect(sf::IntRect(0,0,w,h));
    }
    if(name == "Grass"){
        sprite.setTextureRect(sf::IntRect(32,0,w,h));
    }
    if(name == "Bush"){
        sprite.setTextureRect(sf::IntRect(0,240,w,h));
    }
    if(name == "Elka"){
        sprite.setTextureRect(sf::IntRect(0,140,w,h));
    }
}

void Objects::checkCollisionWithMap(float Dx, float Dy){   //������� �������� ������������ � ������
    for (int i = 0; i < obj.size(); i++){          //���������� �� ��������
        if (getRect().intersects(obj[i].rect)){       //�������� ����������� ������ � �������
            if ((obj[i].name == "solid")||(obj[i].name == "ground")||(obj[i].name == "grass")||(obj[i].name == "border")){
                if (Dy>0){y = obj[i].rect.top - h;  dy = 0; onGround = true; }
                if (Dy<0){y = obj[i].rect.top + obj[i].rect.height;  dy = 0;}
                if (Dx>0){x = obj[i].rect.left - w; dx = -0.1; sprite.scale(-1,1);}
                if (Dx<0){x = obj[i].rect.left + obj[i].rect.width; dx = 0.1; sprite.scale(-1,1);}
            }
        }
    }
}

void Objects::update(sf::View * view, float time){
    if(name == "Metal"){
        if(health <= 0){
            life = false;
        }
        sprite.setPosition(x + w/2, y + h/2);
    }
    if(name == "Gold"){
        if(health <= 0){
            life = false;
        }
        sprite.setPosition(x + w/2, y + h/2);
    }
    if(name == "Berry"){
        if(health <= 0){
            life = false;
        }
        sprite.setPosition(x + w/2, y + h/2);
    }
    if(name == "Market"){
        y += dy*time;
        checkCollisionWithMap(0, dy);
        sprite.setPosition(x + w/2, y + h/2);
        dy = dy + 0.0015*time;
    }
    if(name == "Solid"){
        if((health <= 0)){
            life = false;
        }
        sprite.setPosition(x + w/2, y + h/2);
    }
    if(name == "Info"){
        sprite.setPosition(x + w/2, y + h/2);
    }
    if((name == "Ground")||(name == "Grass")){
        sprite.setPosition(x + w/2, y + h/2);
        if((health <= 0)){
            life = false;
        }
    }
    if((name == "Bush")){
        y += dy*time;
        checkCollisionWithMap(0, dy);
        sprite.setPosition(x + w/2, y + h/2);
        if(health <= 0){
            life = false;
        }
        dy = dy + 0.0015*time;
    }
    if((name == "Elka")){
        y += dy*time;
        checkCollisionWithMap(0, dy);
        sprite.setPosition(x + w/2, y + h/2);
        if(health <= 0){
            life = false;
        }
        dy = dy + 0.0015*time;
    }
}
