#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;    //�������� sfml ������ "���", ������� � �������� �������

View getPlayerCoordinateForView(float x,float y){    //������� ��� ���������� ��������� ������

	float tempX = x; float tempY = y;   //��������� ����� ������ � ��������� ��, ����� ������ ����
    printf("%f  %f\n", tempX, tempY);
	if (x < 320) tempX = 320;    //������� �� ���� ����� �������
	if (y < 240) tempY = 240;    //������� �������
	if (x > 3435) tempX = 3435;  //������ �������
	if (y > 554) tempY = 554;    //������ �������

	view.setCenter(tempX, tempY);       //������ �� �������, ��������� ��� ����������.
	return view;
}
