#include "gameUtils.h"








COORD getRandomMapLocation() {

	srand(time(NULL));

	COORD pos;

	do {
		pos.X = rand() % (mapWidth - 2);
		pos.Y = rand() % (mapHeight - 2);
	} while (pos.X == 0 || pos.Y == 0); // keep randoming if we get 0

	return pos;
}