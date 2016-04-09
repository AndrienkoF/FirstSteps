#include <SFML\Graphics.hpp>
const int HEIGHT_MAP = 25;
const int WIDTH_MAP = 40;


sf::String TileMap[HEIGHT_MAP] = {
	"0000000000000000000000000000000000000000",
	"0            s                         0",
	"0   s    s       s    s                0",
	"0    f   h    s    s       h           0",
	"0              s      f                0",
	"0  f     s  f s                        0",
	"0                           f          0",
	"0           h                          0",
	"0     h                 h              0",
	"0               h                      0",
	"0        f                             0",
	"0     h           f                    0",
	"0         h                            0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0000000000000000000000000000000000000000",
};

void randomMapGenerate(){     // функция рандомного генерирования предметов

	int randomElementX = 0;   //случайный элемент по горизонтали
	int randomElementY = 0;   //случайній элемент по вертикали
	srand(time(0));
	int countStone = 1;       //количество камней

	while (countStone>0){
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);

		if (TileMap[randomElementY][randomElementX] == ' ')   {
			TileMap[randomElementY][randomElementX] = 's';
			countStone--;
		}
	}
}
