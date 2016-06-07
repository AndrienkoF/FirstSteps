#include "menu.h"

void menu(sf::RenderWindow & window) {
    sf::Music music;     //создаем объект музыки
    music.openFromFile("music/menuMusic.ogg");    //загружаем файл
    music.play();    //воспроизводим музыку

	sf::Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("menu/111.png");
	menuTexture3.loadFromFile("menu/333.png");
	menuBackground.loadFromFile("menu/fon.jpg");
	sf::Sprite menu1(menuTexture1), menu3(menuTexture3), menuBg(menuBackground);
	bool isMenu = true;
	int menuNum = 0;
	menu1.setPosition(700, 600);
	menu3.setPosition(1150, 600);
	menuBg.setPosition(0, 0);

	while (isMenu){
		menu1.setColor(sf::Color::White);
		menu3.setColor(sf::Color::White);

		if (sf::IntRect(700, 600, 300, 50).contains(sf::Mouse::getPosition(window))) {
                menu1.setColor(sf::Color::Yellow); menuNum = 1;
        }
		if (sf::IntRect(1150, 600, 300, 50).contains(sf::Mouse::getPosition(window))){
                menu3.setColor(sf::Color::Yellow); menuNum = 3;
        }

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			if (menuNum == 1) {
                isMenu = false;
            }
			if (menuNum == 3) {
                isMenu = false;
                window.close();
            }
		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu3);

		window.display();
	}
}

void menuEnd(sf::RenderWindow & window){
    sf::Music music;     //создаем объект музыки
    music.openFromFile("music/menuMusic.ogg");    //загружаем файл
    music.play();    //воспроизводим музыку

	sf::Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("menu/111.png");
	menuTexture3.loadFromFile("menu/333.png");
	menuBackground.loadFromFile("menu/potracheno.jpg");
	sf::Sprite menu1(menuTexture1), menu3(menuTexture3), menuBg(menuBackground);
	bool isMenu = true;
	int menuNum = 0;
	menu1.setPosition(700, 600);
	menu3.setPosition(1150, 600);
	menuBg.setPosition(0, 0);

	while (isMenu){
		menu1.setColor(sf::Color::White);
		menu3.setColor(sf::Color::White);

		if (sf::IntRect(700, 600, 300, 50).contains(sf::Mouse::getPosition(window))) {
                menu1.setColor(sf::Color::Yellow); menuNum = 1;
        }
		if (sf::IntRect(1150, 600, 300, 50).contains(sf::Mouse::getPosition(window))){
                menu3.setColor(sf::Color::Yellow); menuNum = 3;
        }

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			if (menuNum == 1) {
                isMenu = false;
            }
			if (menuNum == 3) {
                isMenu = false;
                window.close();
            }
		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu3);

		window.display();
	}
}
