#include "classEnemy.h"

Enemy::Enemy(sf::Image &image, sf::String Name, Level &lev, float X, float Y, float W, float H) :Entity(image, Name, X, Y, W, H){
    CurrentFrame = 0;
    CurrentFrame2 = 0;
    obj = lev.GetAllObjects();
    if(name == "EasyEnemy1"){
        sprite.setTextureRect(sf::IntRect(0,0,w,h));
        dx = 0.1;
    }
    if(name == "HardEnemy"){
        sprite.setTextureRect(sf::IntRect(0,0,w,h));
        dx = 0.1;
    }
}

void Enemy::checkCollisionWithMap(float Dx, float Dy){   //функция проверки столкновений с картой
    for (int i = 0; i < obj.size(); i++){                //проходимся по объектам
        if (getRect().intersects(obj[i].rect)){          //проверка пересечения игрока с объктом
            if ((obj[i].name == "solid")||(obj[i].name == "ground")||(obj[i].name == "grass")||(obj[i].name == "cage")||(obj[i].name == "border")){
                if (Dy>0){y = obj[i].rect.top - h;  dy = 0; onGround = true; }
                if (Dy<0){y = obj[i].rect.top + obj[i].rect.height;  dy = 0;}
                if (Dx>0){x = obj[i].rect.left - w; dx = -0.1; sprite.scale(-1,1);}
                if (Dx<0){x = obj[i].rect.left + obj[i].rect.width; dx = 0.1; sprite.scale(-1,1);}
            }
        }
    }
}

void Enemy::update(sf::View * view, float time){
    if(name == "EasyEnemy1"){
        x += dx*time;
        checkCollisionWithMap(dx, 0);
        y += dy*time;
        checkCollisionWithMap(0, dy);
        sprite.setPosition(x + w/2, y + h/2);
        if(health <= 0){
            life = false;
        }
        if(life){
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 2) CurrentFrame -= 2;
            sprite.setTextureRect(sf::IntRect(46 *int(CurrentFrame), 0, 46, 47));
        }
        dy = dy + 0.0015*time;   //постоянно притягиваемся к земле
    }
    if(name == "HardEnemy"){
        x += dx*time;
        checkCollisionWithMap(dx, 0);
        y += dy*time;
        checkCollisionWithMap(0, dy);
        sprite.setPosition(x + w/2, y + h/2);

        if(health <= 0){
            life = false;
        }
        if(life){
            CurrentFrame2 += 0.005*time;
            if (CurrentFrame2 > 4) CurrentFrame2 -= 4;
            sprite.setTextureRect(sf::IntRect(128 * int(CurrentFrame2), 0, 128, 125));
        }
        dy = dy + 0.0015*time;
    }
}
