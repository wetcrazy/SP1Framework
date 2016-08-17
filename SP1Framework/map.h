#ifndef _MAP_H
#define _MAP_H


#include <string>
#include <iostream>
#include <fstream>
#include "Framework\console.h"

using namespace std;

// Original dimension is 83 x 35
const short mapWidth = 83;
const short mapHeight = 35;

enum MAP {

	LEVEL_MENU = 0,
	LEVEL_ONE = 1,
	LEVEL_TWO = 2,
	LEVEL_THREE = 3,
	LEVEL_FOUR = 4,
	LEVEL_FIVE = 5,
	LEVEL_SIX = 6,
	LEVEL_SEVEN = 7,
	LEVEL_EIGHT = 8,
	LEVEL_NINE = 9,
	LEVEL_TEN = 10

};


void renderMap(Console * handle, MAP level, char ptr[][mapHeight]);
void closeMap();


#endif
