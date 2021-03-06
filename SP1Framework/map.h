#ifndef _MAP_H
#define _MAP_H


#include <string>
#include <iostream>
#include <fstream>
#include "Framework\console.h"
#include <vector>
#include "skills.h"
#include "_AI.h"

using namespace std;

// Original dimension is 83 x 35
const short mapWidth = 82;
const short mapHeight = 36;

// Offset to apppend information on the Top and Bottom of the console
const short header_offset = 1;
const short footer_offset = 1;

enum MAP {
	LEVEL_INSTRUCTION = 251,
	LEVEL_WON = 252,
	LEVEL_PAUSE = 253,
	LEVEL_OVER = 254,
	LEVEL_TITLE = 255,
	LEVEL_MENU = 256,
	LEVEL_ONE = 1,
	LEVEL_TWO = 2,
	LEVEL_THREE = 3,
	LEVEL_FOUR=4,
	LEVEL_FIVE = 5,

};

extern MAP LEVEL_restart;
extern MAP current_level;
extern vector< vector<char> > g_Map;
extern vector< vector<char> > g_Map_Cache;

// Draw the entire map vector onto the console
void renderMap(Console * handle);

// Renders fog over the map
void renderFog(Console * handle);

// Closes the file stream & resets all variables upon changing map
void closeMap();

// Clear map and writes the previous g_Map into g_Map_Cache
void closeHalfMap();

// Clears map only
void closeMapOnly();

// Replace the character 'c' with 'sub' once
void replaceMapCharacterOnce(char c, char sub);

// Replace all of character 'c' with 'sub' 
void replaceMapCharacterAll(char c, char sub);

#endif
