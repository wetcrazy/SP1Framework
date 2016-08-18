#ifndef _INTERACTABLE_H
#define _INTERACTABLE_H

#include "map.h"
#include "boulder.h"
#include "star.h"
#include "boulder.h"
#include <list>


// Characters that the player can walk through
const char PASSABLES[20] = {

	' ',
	'+',

};

extern STAR _OBJ_STARS[];

bool isPassable(char c);
void renderObjects(MAP map);
void destroyObjects();

#endif // !_INTERACTABLE_H