#ifndef _INTERACTABLE_H
#define _INTERACTABLE_H

#include "map.h"
#include "boulder.h"
#include "star.h"

// Characters that the player can walk through
const char PASSABLES[20] = {

	' ',
	'*',

};

// Interactables objects
const char INTERACTABLES[20] = {

	'*',

};

extern vector<STAR> _OBJ_COLLECTION_STAR;

bool isPassable(char c);
bool isInteractable(char c);
void updateObjects(MAP map);
void destroyObjects();
size_t findStarAt(COORD pos);


#endif // !_INTERACTABLE_H