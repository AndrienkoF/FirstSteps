#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;//�������� sfml ������ "���", ������� � �������� �������

View getPlayerCoordinateForView(float x,float y) {    //������� ��� ���������� ��������� ������
	view.setCenter(x + 100, y);                       // +100 - �������� ������ �� ���� ������.
	return view;
}
