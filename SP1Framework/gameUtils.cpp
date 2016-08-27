#include "gameUtils.h"








COORD getRandomMapLocation() {

	srand(time(NULL));

	COORD pos = {
		rand() % mapWidth, rand() % mapHeight
	};

	return pos;
}