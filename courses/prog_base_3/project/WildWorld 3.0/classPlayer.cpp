#include "classPlayer.h"

Player::Player(Image &image, String Name, Level &lev, float X, float Y, float W, float H) :Entity(image, Name, X, Y, W, H){
    CurrentFrame = 0;
    state = stay;
    obj = lev.GetAllObjects();   //получаем все объкты с карты
    if(name == "Hero"){
        sprite.setTextureRect(IntRect(0,0,w,h));
    }
}

void Player::control(){
    if (life){
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
    }else{
        state = stay;
        speed = 0;
    }
}

void Player::checkCollisionWithMap(float Dx, float Dy){   //функция проверки столкновений с картой
    for (unsigned int i = 0; i < obj.size(); i++){       //проходимся по объектам
        if (getRect().intersects(obj[i].rect)){          //проверка пересечения игрока с объктом
            if ((obj[i].name == "build")||(obj[i].name == "solid")||(obj[i].name == "ground")||(obj[i].name == "grass")){
                if (Dy>0){y = obj[i].rect.top - h ;  dy = 0; onGround = true;}
                if (Dy<0){y = obj[i].rect.top + obj[i].rect.height ;  dy = 0;}
                if (Dx>0){x = obj[i].rect.left - w ;}
                if (Dx<0){x = obj[i].rect.left + obj[i].rect.width ;}
            }
            if(life){
                if ((Keyboard::isKeyPressed(Keyboard::D))&&((obj[i].name == "bush")||(obj[i].name == "elka"))){
                    obj[i].name = "crashedTree";
                }
                if ((Keyboard::isKeyPressed(Keyboard::S))&&((obj[i].name == "grass")||(obj[i].name == "ground"))){
                    obj[i].name = "crashed";
                }
                if ((Keyboard::isKeyPressed(Keyboard::A))&&(obj[i].name == "easyEnemy1")){
                    obj[i].name = "crashedEnemy";
                }
               /* if ((Keyboard::isKeyPressed(Keyboard::Z))&&(obj[i].name == "crashed")){
                    obj[i].name = "build";
                }*/
            }
        }
    }
}

void Player::update(sf::View * view, float time){  //функция для движения
   control();
    switch(state){
        case right: dx = speed; break;
        case left: dx = -speed; break;
        case jump: break;
        case down: dx = 0; break;
        case stay: dx = 0; break;
    }
    x += dx*time;
    checkCollisionWithMap(dx, 0);
    y += dy*time;
    checkCollisionWithMap(0, dy);

    sprite.setPosition(x + w/2, y + h/2);
    if(health <= 0){
        life = false;
    }
    if(!isMove){
        speed = 0;
    }
    if(life){
        if (Keyboard::isKeyPressed(Keyboard::Right)){
            state = right;
            speed = 0.1;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 3) CurrentFrame -= 3;
            sprite.setTextureRect(IntRect(37 *int(CurrentFrame), 0, 37, 55));
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)){
            state = left;
            speed = 0.1;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 4) CurrentFrame -= 3;
            sprite.setTextureRect(IntRect(37 *int(CurrentFrame), 61, 37, 55));
        }
        if ((Keyboard::isKeyPressed(Keyboard::Up))&& (onGround)){
            state = jump;
            dy = -0.7;
            onGround = false;
        }
        if ((Keyboard::isKeyPressed(Keyboard::Left))&&
           ((Keyboard::isKeyPressed(Keyboard::D))||
            (Keyboard::isKeyPressed(Keyboard::A))||
            (Keyboard::isKeyPressed(Keyboard::S)))){
                if (CurrentFrame > 3) CurrentFrame -= 2;
                sprite.setTextureRect(IntRect(37 *int(CurrentFrame), 251, -37, 55));
            }
        if (((Keyboard::isKeyPressed(Keyboard::D))||
            (Keyboard::isKeyPressed(Keyboard::A))||
            (Keyboard::isKeyPressed(Keyboard::S)))&&(!Keyboard::isKeyPressed(Keyboard::Left))){
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 2) CurrentFrame -= 2;
            sprite.setTextureRect(IntRect(37 *int(CurrentFrame), 251, 37, 55));
        }
        /*if (Mouse::isButtonPressed(Mouse::Left)){
                CurrentFrame += 0.005*time;
                if (CurrentFrame > 2) CurrentFrame -= 2;
                sprite.setTextureRect(IntRect(37 *int(CurrentFrame), 251, 37, 55));
            }*/
    }else{
        state = stay;
        sprite.setTextureRect(IntRect(0 , 188, 37, 55));
    }
    setPlayerCoordinateForView(view, x, y);

    dy = dy + 0.0015*time;   //постоянно притягиваемся к земле
}
