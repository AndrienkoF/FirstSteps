#include <SFML/Graphics.hpp>

using namespace sf;

sf::View view;    //�������� sfml ������ "���", ������� � �������� �������

View setPlayerCoordinateForView(float x,float y){    //������� ��� ���������� ��������� ������

	float tempX = x; float tempY = y;   //��������� ����� ������ � ��������� ��, ����� ������ ����
    //printf("%f  %f\n", tempX, tempY);
	if (x < 600) tempX = 600;    //������� �� ���� ����� �������
	if (y < 400) tempY = 400;    //������� �������
	if (x > 1600) tempX = 1600;  //������ �������
    if (y > 550) tempY = 550;    //������ �������


	view.setCenter(tempX, tempY);       //������ �� �������, ��������� ��� ����������.
	return view;
}
