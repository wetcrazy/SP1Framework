#ifndef _INTERACTABLE_H
#define _INTERACTABLE_H


#include <random>
#include <time.h>
#include "map.h"
#include "star.h"
#include "portal.h"
#include "exit.h"


enum INTERACTABLES {

	I_STAR = '*',
	I_PORTAL = 'O',
	I_EXIT_INACTIVE = '#',
	I_EXIT_ACTIVE = 'o'

};

// Characters that the player can walk through
const char PASSABLES[] = {

	' ',
	'*',
	'O',
	'o'

};

// Interactables objects
const char INTERACTABLES[] = {

	'*',
	'O',
	'#'

};

extern vector<STAR> _COLLECTION_OBJ_STAR;
extern vector<PORTAL> _COLLECTION_OBJ_PORTAL;
extern vector<EXIT> _COLLECTION_OBJ_EXIT;

// Is this an passable object?
bool isPassable(char c);

// Is this an interactable object?
bool isInteractable(char c);

// Runs object logic every frame
void updateObjects(Console * handle, MAP map);

// Removes the entire objects on the map
void destroyObjects();

// Retrieve an instance of the 'star' that the player is standing on
STAR findStarAt(COORD pos);

// Retrieve an instance of the 'portal' that the player is standing on
PORTAL findPortalAt(COORD pos);

// Make all exits passable
void activateExit();

// Make all exits un-passable
void deactivateExit();

#endif // !_INTERACTABLE_H