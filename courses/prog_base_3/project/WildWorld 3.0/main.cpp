#include "game.h"

int main(){
    void(*cb)(void) = checkGamePlay;
    runningGame(cb);
	return 0;
}
