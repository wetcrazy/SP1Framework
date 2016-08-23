#ifndef _MAP_H
#define _MAP_H


#include <string>
#include <iostream>
#include <fstream>
#include "Framework\console.h"
#include <vector>


using namespace std;

// Original dimension is 83 x 35
const short mapWidth = 82;
const short mapHeight = 36;

// Offset to apppend information on the Top and Bottom of the console
const short header_offset = 1;
const short footer_offset = 1;

enum MAP {

	LEVEL_TITLE = 255,
	LEVEL_MENU = 256,
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

extern MAP LEVEL_restart;
extern MAP current_level;
extern vector< vector<char> > g_Map;

void renderMap(Console * handle);
void renderFog(Console * handle);
void closeMap();


#endif
