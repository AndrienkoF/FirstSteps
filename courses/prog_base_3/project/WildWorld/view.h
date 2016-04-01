#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;//объ€вили sfml объект "вид", который и €вл€етс€ камерой

View getPlayerCoordinateForView(float x,float y) {    //функци€ дл€ считывани€ координат игрока
	view.setCenter(x + 100, y);                       // +100 - сместили камеру по иксу вправо.
	return view;
}
