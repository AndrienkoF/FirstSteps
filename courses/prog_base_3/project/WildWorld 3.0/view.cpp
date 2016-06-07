#include "view.h"

void setPlayerCoordinateForView(sf::View * view, float x,float y){    //������� ��� ���������� ��������� ������
	float tempX = x; float tempY = y;   //��������� ����� ������ � ��������� ��, ����� ������ ����
	if (x < 600) tempX = 600;    //������� �� ���� ����� �������
	if (y < 400) tempY = 400;    //������� �������
	if (x > 5800) tempX = 5800;  //������ �������
    if (y > 550) tempY = 550;    //������ �������

	view->setCenter(tempX, tempY);       //������ �� �������, ��������� ��� ����������.
}
