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
	//menu(window);

	View view;
    view.reset(sf::FloatRect(0, 0, 1200, 600));              //размер "вида" камеры

    ////////////////////////// ШРИФТ /////////////////////////////////////////////////////////////////////////////
    Font font;
    font.loadFromFile("font/Belepotan.ttf");   //файл шрифта

    Text text("", font, 20);
    text.setColor(Color::Black);

    Text textInfo("", font, 20);
    textInfo.setColor(Color::Black);

    Text textEnd("", font, 80);
    textEnd.setColor(Color::Red);

    /*Text textGround("", font, 20);
    textG.setColor(Color::Black);*/
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Level lvl;  //создали экземпляр класса уровень
    lvl.LoadFromFile("map.tmx");

    ///////////////////////// ЗВУКИ //////////////////////////////////////////////////////////////////////////////
    Music music;                              //создаем объект музыки
    music.openFromFile("music/music.ogg");    //загружаем файл
    //music.play();                           //воспроизводим музыку
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Image infoFonIm;
	infoFonIm.loadFromFile("images/infoFon.jpg");
	Texture infoFonT;
	infoFonT.loadFromImage(infoFonIm);
	Sprite infoFonSp;
	infoFonSp.setTexture(infoFonT);
	infoFonSp.setTextureRect(IntRect(0, 0, 1152, 598));
	infoFonSp.setScale(0.9f, 0.8f);

    Image heroImage;
    heroImage.loadFromFile("images/Hero2.png");

    Image infoImage;
    infoImage.loadFromFile("images/info.png");

    Image hardEnemyIm;
    hardEnemyIm.loadFromFile("images/monkey.png");

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
    for (unsigned int i = 0; i < elkaList.size(); i++){
        elki.push_back(new Objects(treeImage, "Elka", lvl, elkaList[i].rect.left, elkaList[i].rect.top, 85, 60));
    }

    std::vector<Object> bushList = lvl.GetObjects("bush");
    for (unsigned int i = 0; i < bushList.size(); i++){
        bushes.push_back(new Objects(treeImage, "Bush", lvl, bushList[i].rect.left, bushList[i].rect.top, 48, 40));
    }

    std::vector<Object> grassList = lvl.GetObjects("grass");
    for (unsigned int i = 0; i < grassList.size(); i++){
        grass.push_back(new Objects(groundImage, "Grass", lvl, grassList[i].rect.left, grassList[i].rect.top, 32, 32));
    }

    std::vector<Object> groundList = lvl.GetObjects("ground");
    for (unsigned int i = 0; i < groundList.size(); i++){
        grounds.push_back(new Objects(groundImage, "Ground", lvl, groundList[i].rect.left, groundList[i].rect.top, 32, 32));
    }

    std::vector<Object> easyEnemy1List = lvl.GetObjects("easyEnemy");
    for (unsigned int i = 0; i < easyEnemy1List.size(); i++){
        entities.push_back(new Enemy(easyEnemy1Image, "EasyEnemy1", lvl, easyEnemy1List[i].rect.left, easyEnemy1List[i].rect.top, 46, 45));
    }

    Object info = lvl.GetObject("info");
    Objects myInfo(infoImage, "Info", lvl, info.rect.left, info.rect.top, 96, 96);

    Object hardEnemy = lvl.GetObject("hardEnemy");
    Enemy monkey(hardEnemyIm, "HardEnemy", lvl, hardEnemy.rect.left, hardEnemy.rect.top, 128, 125);

    Object player = lvl.GetObject("player");
    Player hero(heroImage, "Hero", lvl, player.rect.left, player.rect.top, 37, 55);

    float moveTimer = 0;
    int treesScore = 0, groundScore = 0;
    bool showInfo = true;
    //Vector2i mouseClickPos;

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

            if (event.type == Event::KeyPressed){
                if (event.key.code == Keyboard::I){
                    switch (showInfo){
                        case true: {
                            infoFonSp.setPosition(50, 150);
                            showInfo = false;
                            break;
                        }
                        case false:{
                            showInfo = true;
                            break;
                        }
                    }
                }
            }
        }

        myInfo.update(&view, time);
        monkey.update(&view, time);
        hero.update(&view, time);
        for (it = entities.begin(); it != entities.end();){
            Entity *b = *it;
            b->update(&view, time);
            if (b->life == false){
                it = entities.erase(it);
                delete b;
            }else{
                it++;
            }
        }
        for (it = elki.begin(); it != elki.end();){
            Entity *e = *it;
            e->update(&view, time);
            if (e->life == false){
                it = elki.erase(it);
                delete e;
            }else{
                it++;
            }
        }
        for (it = bushes.begin(); it != bushes.end();){
            Entity *b = *it;
            b->update(&view, time);
            if (b->life == false){
                it = bushes.erase(it);
                delete b;
            }else{
                it++;
            }
        }
        for (it = grounds.begin(); it != grounds.end();){
            Entity *g = *it;
            g->update(&view, time);
            if (g->life == false){
                it = grounds.erase(it);
                delete g;
            }else{
                it++;
            }
        }
        for (it = grass.begin(); it != grass.end();){
            Entity *gr = *it;
            gr->update(&view, time);
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
                    if ((Keyboard::isKeyPressed(Keyboard::E))){
                        if((moveTimer>5000)){
                            (*it)->dx = 0;
                            (*it)->health = 0;
                            treesScore++;
                            moveTimer = 0;
                        }
                    }
                }
            }
        }
        for (it = bushes.begin(); it != bushes.end(); it++){
            if ((*it)->getRect().intersects(hero.getRect())){   //если объект пересекается с игроком
                if ((*it)->name == "Bush"){
                    if ((Keyboard::isKeyPressed(Keyboard::E)&&(moveTimer>5000))){
                        (*it)->dx = 0;
                        (*it)->health = 0;
                        treesScore++;
                        moveTimer = 0;
                    }
                }
            }
        }
        for (it = grass.begin(); it != grass.end(); it++){
            if ((*it)->getRect().intersects(hero.getRect())){   //если объект пересекается с игроком
                if ((*it)->name == "Grass"){
                    if ((Keyboard::isKeyPressed(Keyboard::Space))){
                        (*it)->dx = 0;
                        (*it)->health = 0;
                    }
                }
            }
        }
        for (it = grounds.begin(); it != grounds.end(); it++){
            if ((*it)->getRect().intersects(hero.getRect())){   //если объект пересекается с игроком
                if ((*it)->name == "Ground"){
                    if ((Keyboard::isKeyPressed(Keyboard::Space))){
                        (*it)->dx = 0;
                        (*it)->health = 0;
                        groundScore++;
                    }
                }
            }
        }
        for (it = entities.begin(); it != entities.end(); it++){
            if ((*it)->getRect().intersects(hero.getRect())){   //если объект пересекается с игроком
                if ((*it)->name == "EasyEnemy1"){
                    if (Keyboard::isKeyPressed(Keyboard::Q)){
                        (*it)->dx = 0;
                        (*it)->health = 0;
                    }else{
                        if(moveTimer>2000){
                            hero.health -= 20;
                            moveTimer = 0;
                        }
                    }
                }
            }
        }
/*
        for (it = entities.begin(); it != entities.end(); it++){
            for (it2 = entities.begin(); it2 != entities.end(); it2++){
                if ((*it)->getRect() != (*it2)->getRect()){   //если разные прямоугольники
                    if (((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->name == "EasyEnemy1") && ((*it2)->name == "EasyEnemy1")){  //если столкнутся два врага
                        (*it)->dx *= -1;
                        (*it)->sprite.scale(-1,1);
                    }
                }
            }
        }*/

        window.setView(view);
		window.clear();
		lvl.Draw(window); //рисуем карту

        //////////////////////////////////////// ТЕКСТ ///////////////////////////////////////////////////////////////
        std::ostringstream treesText;
        treesText << treesScore;
		text.setString("Trees: " + treesText.str());
		text.setPosition(view.getCenter().x + 0, view.getCenter().y - 240);
		window.draw(text);

        std::ostringstream groundText;
		groundText << groundScore;
		text.setString("Ground:" + groundText.str());
		text.setPosition(view.getCenter().x - 310, view.getCenter().y - 240);
		window.draw(text);

		if (hero.info == true){
            textInfo.setString("Press \"i\" ");
            textInfo.setPosition(view.getCenter().x - 510, view.getCenter().y - 150);
            window.draw(textInfo);
        }

        if(hero.health >= 0){
            std::ostringstream playerHealthString;
            playerHealthString << hero.health;
            text.setString("Health: " + playerHealthString.str());
            text.setPosition(view.getCenter().x + 125, view.getCenter().y - 240);
            window.draw(text);
        }else{
            text.setString("Health: 0");
            text.setPosition(view.getCenter().x + 125, view.getCenter().y - 240);
            window.draw(text);

            textEnd.setString("WASTED !");
            textEnd.setPosition(view.getCenter().x - 100, view.getCenter().y - 200);
            window.draw(textEnd);
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        window.draw(myInfo.sprite);
        window.draw(monkey.sprite);
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
		if (!showInfo) {
            infoFonSp.setPosition(50, 150);   //позиция фона
			window.draw(infoFonSp);
        }
		window.display();
	}
	return 0;
}
