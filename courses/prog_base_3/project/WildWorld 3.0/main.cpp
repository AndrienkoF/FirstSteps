#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include "view.h"
#include "level.h"
#include "classEntity.h"
#include "classPlayer.h"
#include "classEnemy.h"
#include "classObjects.h"
#include "menu.h"

using namespace sf;   //включаем пространство имен sf (sf::)

int main(){
	RenderWindow window(VideoMode(1366, 768), "WildWorld", Style::Fullscreen);
	menu(window);
    view.reset(sf::FloatRect(0, 0, 1200, 600));              //размер "вида" камеры

    ////////////////////////// ШРИФТ /////////////////////////////////////////////////////////////////////////////
    Font font;
    font.loadFromFile("font/Belepotan.ttf");   //файл шрифта

    Text text("", font, 20);
    text.setColor(Color::Black);

    /*Text textGround("", font, 20);
    textG.setColor(Color::Black);*/
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Level lvl;  //создали экземпляр класса уровень
    lvl.LoadFromFile("map.tmx");

    Music music;     //создаем объект музыки
    music.openFromFile("music/music.ogg");    //загружаем файл
    music.play();    //воспроизводим музыку

    Image heroImage;
    heroImage.loadFromFile("images/Hero2.png");

    Image easyEnemy1Image;
    easyEnemy1Image.loadFromFile("images/Goat.png");

    Image groundImage;
    groundImage.loadFromFile("images/ground.png");

    Image treeImage;
    treeImage.loadFromFile("images/trees.png");

    std::list<Entity*> entities;       //создаем список
    std::list<Entity*> grounds;
    std::list<Entity*> grass;
    std::list<Entity*> bushes;
    std::list<Entity*> elki;
    std::list<Entity*>::iterator it;   //итератор, чтобы проходить по элементам списка
    std::list<Entity*>::iterator it2;

    std::vector<Object> elkaList = lvl.GetObjects("elka");
    for (int i = 0; i < elkaList.size(); i++){
        elki.push_back(new Objects(treeImage, "Elka", lvl, elkaList[i].rect.left, elkaList[i].rect.top, 85, 60));
    }

    std::vector<Object> bushList = lvl.GetObjects("bush");
    for (int i = 0; i < bushList.size(); i++){
        bushes.push_back(new Objects(treeImage, "Bush", lvl, bushList[i].rect.left, bushList[i].rect.top, 48, 40));
    }

    std::vector<Object> grassList = lvl.GetObjects("grass");
    for (int i = 0; i < grassList.size(); i++){
        grass.push_back(new Objects(groundImage, "Grass", lvl, grassList[i].rect.left, grassList[i].rect.top, 32, 32));
    }

    std::vector<Object> groundList = lvl.GetObjects("ground");
    for (int i = 0; i < groundList.size(); i++){
        grounds.push_back(new Objects(groundImage, "Ground", lvl, groundList[i].rect.left, groundList[i].rect.top, 32, 32));
    }

    std::vector<Object> easyEnemy1List = lvl.GetObjects("easyEnemy");
    for (int i = 0; i < easyEnemy1List.size(); i++){
        entities.push_back(new Enemy(easyEnemy1Image, "EasyEnemy1", lvl, easyEnemy1List[i].rect.left, easyEnemy1List[i].rect.top, 46, 45));
    }

    Object player = lvl.GetObject("player");
    Player hero(heroImage, "Hero", lvl, player.rect.left, player.rect.top, 37, 50);

    float moveTimer = 0;

    Clock clock;    //создаем переменную времени, привязка ко времени(а не загруженности/мощности процессора).
    while (window.isOpen()){
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();     //перезагружает время
        time = time / 800;   //скорость игры
        moveTimer += time;

		Event event;
		while (window.pollEvent(event)){
            if ((event.type == sf::Event::Closed)||(Keyboard::isKeyPressed(Keyboard::Escape)))
            window.close();
        }

        hero.update(time);
        for (it = entities.begin(); it != entities.end();){
            Entity *b = *it;
            b->update(time);
            if (b->life == false){
                it = entities.erase(it);
                delete b;
            }else{
                it++;
            }
        }
        for (it = elki.begin(); it != elki.end();){
            Entity *e = *it;
            e->update(time);
            if (e->life == false){
                it = elki.erase(it);
                delete e;
            }else{
                it++;
            }
        }
        for (it = bushes.begin(); it != bushes.end();){
            Entity *b = *it;
            b->update(time);
            if (b->life == false){
                it = bushes.erase(it);
                delete b;
            }else{
                it++;
            }
        }
        for (it = grounds.begin(); it != grounds.end();){
            Entity *g = *it;
            g->update(time);
            if (g->life == false){
                it = grounds.erase(it);
                delete g;
            }else{
                it++;
            }
        }
        for (it = grass.begin(); it != grass.end();){
            Entity *gr = *it;
            gr->update(time);
            if (gr->life == false){
                it = grass.erase(it);
                delete gr;
            }else{
                it++;
            }
        }

        for (it = elki.begin(); it != elki.end(); it++){
            if ((*it)->getRect().intersects(hero.getRect())){   //если объект пересекается с игроком
                if ((*it)->name == "Elka"){
                    if ((Keyboard::isKeyPressed(Keyboard::D))){
                        (*it)->dx = 0;
                        (*it)->health = 0;
                    }
                }
            }
        }
        for (it = bushes.begin(); it != bushes.end(); it++){
            if ((*it)->getRect().intersects(hero.getRect())){   //если объект пересекается с игроком
                if ((*it)->name == "Bush"){
                    if ((Keyboard::isKeyPressed(Keyboard::D))){
                        (*it)->dx = 0;
                        (*it)->health = 0;
                    }
                }
            }
        }
        for (it = grass.begin(); it != grass.end(); it++){
            if ((*it)->getRect().intersects(hero.getRect())){   //если объект пересекается с игроком
                if ((*it)->name == "Grass"){
                    if ((Keyboard::isKeyPressed(Keyboard::S))){
                        (*it)->dx = 0;
                        (*it)->health = 0;
                    }
                }
            }
        }
        for (it = grounds.begin(); it != grounds.end(); it++){
            if ((*it)->getRect().intersects(hero.getRect())){   //если объект пересекается с игроком
                if ((*it)->name == "Ground"){
                    if ((Keyboard::isKeyPressed(Keyboard::S))){
                        (*it)->dx = 0;
                        (*it)->health = 0;
                    }
                }
            }
        }

        for (it = entities.begin(); it != entities.end(); it++){
            if ((*it)->getRect().intersects(hero.getRect())){   //если объект пересекается с игроком
                if ((*it)->name == "EasyEnemy1"){
                    if (/*(hero.dy > 0)&&(hero.onGround == false)&&*/(Keyboard::isKeyPressed(Keyboard::A))){
                        (*it)->dx = 0;
                        (*it)->health = 0;
                    }else{
                        if(moveTimer>2000){
                            hero.health -= 10;
                            moveTimer = 0;
                        }
                    }
                }
            }
        }

        for (it = entities.begin(); it != entities.end(); it++){
            for (it2 = entities.begin(); it2 != entities.end(); it2++){
                if ((*it)->getRect() != (*it2)->getRect()){   //если разные прямоугольники
                    if (((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->name == "EasyEnemy1") && ((*it2)->name == "EasyEnemy1")){  //если столкнутся два врага
                        (*it)->dx *= -1;
                        (*it)->sprite.scale(-1,1);
                    }
                }
            }
        }

        window.setView(view);
		window.clear();
		lvl.Draw(window); //рисуем карту

        //////////////////////////////////////// ТЕКСТ ///////////////////////////////////////////////////////////////
        std::ostringstream treesScore;
		treesScore << hero.treesScore;
		text.setString("Trees: " + treesScore.str());
		text.setPosition(view.getCenter().x + 0, view.getCenter().y - 240);
		window.draw(text);

        std::ostringstream groundScore;
		groundScore << hero.groundScore;
		text.setString("Ground:" + groundScore.str());
		text.setPosition(view.getCenter().x - 310, view.getCenter().y - 240);
		window.draw(text);

        std::ostringstream playerHealthString;
		playerHealthString << hero.health;
		text.setString("Helth: " + playerHealthString.str());
		text.setPosition(view.getCenter().x + 125, view.getCenter().y - 240);
		window.draw(text);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        for (it = elki.begin(); it != elki.end(); it++){
            window.draw((*it)->sprite);
        }
        for (it = bushes.begin(); it != bushes.end(); it++){
            window.draw((*it)->sprite);
        }
        for (it = grass.begin(); it != grass.end(); it++){
            window.draw((*it)->sprite);
        }
        for (it = grounds.begin(); it != grounds.end(); it++){
            window.draw((*it)->sprite);
        }
        for (it = entities.begin(); it != entities.end(); it++){
            window.draw((*it)->sprite);
        }
		window.draw(hero.sprite);     //выводим спрайт на экран
		window.display();
	}
	return 0;
}
