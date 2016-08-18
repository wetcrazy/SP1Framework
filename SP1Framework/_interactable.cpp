#include "_interactable.h"
#include "game.h"
#include "map.h"

vector<STAR> _OBJ_COLLECTION_STAR;


// Test if the argument is a passable ASCII character
bool isPassable(char c) {
	for each (char ch in PASSABLES) {
		if (c == ch)
			return true;
	}
	return false;
}

bool isInteractable(char c) {
	for each (char ch in INTERACTABLES) {
		if (c == ch)
			return true;
	}
	return false;
}


// Object logic goes here
void updateObjects(MAP map) {

	switch (map) {
	case LEVEL_TITLE:
		break;
	case LEVEL_MENU:
		break;
	case LEVEL_ONE:
		if (g_sChar.below == '*') {
			g_Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = 'A';
		}
		break;
	case LEVEL_TWO:
		break;
	case LEVEL_THREE:
		break;
	case LEVEL_FOUR:
		break;
	case LEVEL_FIVE:
		break;
	case LEVEL_SIX:
		break;
	case LEVEL_SEVEN:
		break;
	case LEVEL_EIGHT:
		break;
	case LEVEL_NINE:
		break;
	case LEVEL_TEN:
		break;
	}


}