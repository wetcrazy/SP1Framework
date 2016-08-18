#ifndef _INTERACTABLE_H
#define _INTERACTABLE_H

#include "map.h"
#include "boulder.h"


// ASCII Characters that the player can walk through
const char PASSABLES[20] = {

	' ',
	'+',

};


bool isPassable(char c);
void renderObjects(MAP map);
void destroyObjects();

#endif // !_INTERACTABLE_H