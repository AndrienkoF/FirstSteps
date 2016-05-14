#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include "level.h"

using namespace sf;

/////////////////////////////////////////// КЛАСС ИГРОКА /////////////////////////////////////////////////////////
class Player: public Entity{
public:
    enum{left, right, up, down, jump, stay}state;
    int groundScore, treesScore, meatScore;
    float CurrentFrame;

    Player (Image &image, String Name, Level &lev, float X, float Y, float W, float H) :Entity(image, Name, X, Y, W, H){
        groundScore = 0, treesScore = 0, meatScore = 0, CurrentFrame = 0;
        state = stay;
        obj = lev.GetAllObjects();   //получаем все объкты с карты
        if(name == "Hero"){
            sprite.setTextureRect(IntRect(0,0,w,h));
        }
    }

    void control(){
        if (Keyboard::isKeyPressed){
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
            if (Keyboard::isKeyPressed(Keyboard::Down)){
                state = down;
            }
        }
    }

    void checkCollisionWithMap(float Dx, float Dy, float time){   //функция проверки столкновений с картой
        moveTimer += time;
		for (int i = 0; i < obj.size(); i++)   //проходимся по объектам
		if (getRect().intersects(obj[i].rect)){   //проверка пересечения игрока с объктом
			if ((obj[i].name == "solid")||(obj[i].name == "ground")||(obj[i].name == "grass")){
				if (Dy>0){y = obj[i].rect.top - h ;  dy = 0; onGround = true;}
				if (Dy<0){y = obj[i].rect.top + obj[i].rect.height ;  dy = 0;}
				if (Dx>0){x = obj[i].rect.left - w ;}
				if (Dx<0){x = obj[i].rect.left + obj[i].rect.width ;}
			}
			if ((Keyboard::isKeyPressed(Keyboard::D))&&((obj[i].name == "bush")||(obj[i].name == "elka"))){
                //if(moveTimer > 2000){
                    treesScore++;
                    obj[i].name = "crashed";
                //    moveTimer = 0;
                //}
            }
			if ((Keyboard::isKeyPressed(Keyboard::S))&&((obj[i].name == "grass")||(obj[i].name == "ground"))){
                //if(moveTimer > 2000){
                    groundScore++;
                    obj[i].name = "crashed";
                //    moveTimer = 0;
                //}
            }
		}
	}

    void update(float time){  //функция для движения
        control();
        switch(state){
            case right: dx = speed; break;
            case left: dx = -speed; break;
            case up: break;
            case down: dx = 0; break;
            case stay: dx = 0; break;
		}
		x += dx*time;
		checkCollisionWithMap(dx, 0, time);

		y += dy*time;
		checkCollisionWithMap(0, dy, time);

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
        }else{
            state = stay;
            sprite.setTextureRect(IntRect(0 , 181, 26, 37));
        }
        setPlayerCoordinateForView(x, y);
        dy = dy + 0.0015*time;   //постоянно притягиваемся к земле
    }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

