#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;    //�������� sfml ������ "���", ������� � �������� �������

View getPlayerCoordinateForView(float x,float y){    //������� ��� ���������� ��������� ������
	view.setCenter(x + 100, y);                      // +100 - �������� ������ �� ���� ������.
	return view;
}

View viewMap(float time){   //������� ��� ����������� ������ �� �����. ��������� ����� sfml
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		view.move(0.1*time, 0);     //�������� ����� ������
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		view.move(0, 0.1*time);     //�������� ����� ����
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		view.move(-0.1*time, 0);    //�������� ����� �����
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		view.move(0, -0.1*time);    //�������� ����� ������
	}

    return view;
}
