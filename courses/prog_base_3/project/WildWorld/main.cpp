#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"      //���������� ��� � ������
#include "view.h"     //���������� ��� � ����� ������

using namespace sf;  //�������� ������������ ���� sf, ����� ��������� �� ������ sf::

/////////////////////////////////////////// ����� ������ /////////////////////////////////////////////////////////

class Player {

private: float x, y = 0;             //�������� ����������, � ������������ Player ���� ����� �� ��������
public:
	float w, h, dx, dy, speed;   // dx dy speed ����� = 0 � ������������ ������ ����
    int dir;                     //����������� (��������) ������
    String File;
    Image image;                 //�����������
    Texture texture;             //��������
    Sprite sprite;               //������

    Player (String F, float X, float Y, float W, float H){
        File = F;
        float w = W;
        float h = H;
        image.loadFromFile("images/" + File);      //���������� ���� �����������
        //image.createMaskFromColor(Color( , , )); //����� ������ ��������� ���� !!!
        texture.loadFromImage(image);              //���������� ����������� � ��������
        sprite.setTexture(texture);                //�������� ������ ���������
        x = X, y = Y;                              //���������� ��������� �������
        sprite.setTextureRect(IntRect(0,0,w,h));   //������ ������� �������������
    }

    void update(float time){ //������� ��� ��������
        switch(dir){
        case 0:
            dx = speed;
            dy = 0;
            break;
        case 1:
            dx = -speed;
            dy = 0;
            break;
        case 2:
            dx = 0;
            dy = speed;
            break;
        case 3:
            dx = 0;
            dy = -speed;
            break;
        }

        x += dx*time;
        y += dy*time;

        speed = 0;
        sprite.setPosition(x,y);
    }

    float getPlayerCoordinateX(){	//���� ������� ����� �������� ���������� �
        return x;
    }
    float getPlayerCoordinateY(){	//���� ������� ����� �������� ���������� Y
        return y;
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){
	RenderWindow window(VideoMode(640, 480), "WildWorld");  //��������� ��� �������� ������ ����
    view.reset(sf::FloatRect(0, 0, 640, 480));              //������ "����" ������

    Image map_image;                                        //������ ����������� ��� �����
	map_image.loadFromFile("images/map.png");               //��������� ���� ��� �����
	Texture map;                                            //�������� �����
	map.loadFromImage(map_image);                           //�������� �������� ���������
	Sprite s_map;                                           //������ ������ ��� �����
	s_map.setTexture(map);                                  //�������� �������� ��������

    Player hero("allHero.png", 250, 250, 48, 56);

    float CurrentFrame = 2;
    Clock clock; //������� ���������� �������, �������� �� �������(� �� �������������/�������� ����������).

	while (window.isOpen()){

	    float time = clock.getElapsedTime().asMicroseconds(); //���� ��������� ����� � �������������
        clock.restart();                                      //������������� �����
        time = time/800;                                      //�������� ����
		//std::cout << time << "\n";                          //������� ��� ����� ����� (���������������, ��� �����)

		Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}

        ///////////////////////////////// ���������� ���������� "HERO" //////////////////////////////////////////////////
		if ((Keyboard::isKeyPressed(Keyboard::Right))){ //���� ������ ������� ������� ����� ��� ���� ����� �
			hero.dir = 0;
			hero.speed = 0.1;
			CurrentFrame += 0.005*time;                 //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (CurrentFrame > 5) CurrentFrame -= 3;    // ���� ������ � �������� ����� - ������������ �����.
			hero.sprite.setTextureRect(IntRect(46 *int(CurrentFrame), 0, 46, 56));
            getPlayerCoordinateForView(hero.getPlayerCoordinateX(), hero.getPlayerCoordinateY());   //�������� ���������� ������ � ������� ���������� �������
		}
		if ((Keyboard::isKeyPressed(Keyboard::Left))){  //���� ������ ������� ������� ����� ��� ���� ����� �
			hero.dir = 1;
			hero.speed = 0.1;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 5) CurrentFrame -= 2;
			hero.sprite.setTextureRect(IntRect(46 *int(CurrentFrame), 0, -46, 56));
			getPlayerCoordinateForView(hero.getPlayerCoordinateX(), hero.getPlayerCoordinateY());   //�������� ���������� ������ � ������� ���������� �������
		}
        if ((Keyboard::isKeyPressed(Keyboard::Up))){
                hero.dir = 3;
                hero.speed = 0.1;
                hero.sprite.setTextureRect(IntRect(144, 112, 48, 56));
                getPlayerCoordinateForView(hero.getPlayerCoordinateX(), hero.getPlayerCoordinateY());   //�������� ���������� ������ � ������� ���������� �������
        }
        if ((Keyboard::isKeyPressed(Keyboard::Down))){
                hero.dir = 2;
                hero.speed = 0.1;
                hero.sprite.setTextureRect(IntRect(92, 112, 48, 56));
                getPlayerCoordinateForView(hero.getPlayerCoordinateX(), hero.getPlayerCoordinateY());   //�������� ���������� ������ � ������� ���������� �������
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////

        hero.update(time);
        window.setView(view);     //"��������" ������ � ���� sfml
		window.clear();

		/////////////////////////////////////////////  ������ �����  /////////////////////////////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++){
			if (TileMap[i][j] == ' ')   s_map.setTextureRect(IntRect(0, 0, 32, 32));  //���� ��������� ������ ������, �� ������ 1� ���������
			if (TileMap[i][j] == 's')   s_map.setTextureRect(IntRect(32, 0, 32, 32)); //���� ��������� ������ s, �� ������ 2� ���������
			if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32)); //���� ��������� ������ 0, �� ������ 3� ���������

			s_map.setPosition(j * 32, i * 32);    //������ ������� �� ��� �������
			window.draw(s_map);                   //������ ���������� �� �����
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////

		window.draw(hero.sprite);     //������� ������ �� �����
		window.display();
	}

	return 0;
}
