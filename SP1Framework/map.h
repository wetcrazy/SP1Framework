#ifndef _MAP_H
#define _MAP_H


#include <string>
#include <iostream>
#include <fstream>
#include "Framework\console.h"

using namespace std;

const short mapWidth = 53;
const short mapHeight = 33;

enum MAP {

	LEVEL_ONE,
	LEVEL_TWO,
	LEVEL_THREE,
	LEVEL_FOUR,
	LEVEL_FIVE,
	LEVEL_SIX,
	LEVEL_SEVEN,
	LEVEL_EIGHT,
	LEVEL_NINE,
	LEVEL_TEN

};


void renderMap(Console * handle, MAP level, char ptr[][mapHeight]);
void closeMap();


#endif
