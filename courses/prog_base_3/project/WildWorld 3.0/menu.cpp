#include "menu.h"

void menu(sf::RenderWindow & window) {
    sf::Music music;     //создаем объект музыки
    music.openFromFile("music/menuMusic.ogg");    //загружаем файл
    music.play();    //воспроизводим музыку

	sf::Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("menu/111.png");
	menuTexture2.loadFromFile("menu/222.png");
	menuTexture3.loadFromFile("menu/333.png");
	aboutTexture.loadFromFile("menu/Penguins.jpg");
	menuBackground.loadFromFile("menu/fon.jpg");
	sf::Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(650, 600);
	menu2.setPosition(880, 600);
	menu3.setPosition(1150, 600);
	menuBg.setPosition(0, 0);

	while (isMenu){
		menu1.setColor(sf::Color::White);
		menu2.setColor(sf::Color::White);
		menu3.setColor(sf::Color::White);

		if (sf::IntRect(650, 600, 300, 50).contains(sf::Mouse::getPosition(window))) {
                menu1.setColor(sf::Color::Yellow); menuNum = 1;
        }
		if (sf::IntRect(880, 600, 300, 50).contains(sf::Mouse::getPosition(window))) {
                menu2.setColor(sf::Color::Yellow); menuNum = 2;
        }
		if (sf::IntRect(1150, 600, 300, 50).contains(sf::Mouse::getPosition(window))){
                menu3.setColor(sf::Color::Yellow); menuNum = 3;
        }

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			if (menuNum == 1) {
                isMenu = false;
            }
			if (menuNum == 2) {
                window.draw(about);
                window.display();
                while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
            }
			if (menuNum == 3) {
			    window.close();
                isMenu = false;
            }

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}
}
