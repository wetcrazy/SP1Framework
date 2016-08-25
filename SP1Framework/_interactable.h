#ifndef _INTERACTABLE_H
#define _INTERACTABLE_H


#include <random>
#include <time.h>
#include "map.h"
#include "star.h"
#include "portal.h"
#include "exit.h"
#include "trap.h"
#include "shield.h"


enum INTERACTABLES {

	I_STAR = '*',
	I_PORTAL = 'O',
	I_EXIT_INACTIVE = '#',
	I_EXIT_ACTIVE = 'o',
	I_TRAP = '!',
	I_SHIELD = '~'

};

// Characters that the player can walk through
const char PASSABLES[] = {

	' ',
	I_STAR,
	I_PORTAL,
	I_EXIT_ACTIVE,
	I_TRAP

};

// Interactables objects
const char INTERACTABLES[] = {

	I_STAR,
	I_PORTAL,
	I_EXIT_ACTIVE,
	I_EXIT_INACTIVE,
	I_TRAP,
	I_SHIELD

};


extern vector<STAR> _COLLECTION_OBJ_STAR;
extern vector<PORTAL> _COLLECTION_OBJ_PORTAL;
extern vector<EXIT> _COLLECTION_OBJ_EXIT;
extern vector<TRAP> _COLLECTION_OBJ_TRAP;
extern short _COLLECTION_OBJ_SHIELD_COUNT;

// Is this an passable object?
bool isPassable(char c);

// Is this an interactable object?
bool isInteractable(char c);

// Runs object logic every frame
void updateObjects(Console * handle, MAP map, double eTime);

// Removes the entire objects on the map
void destroyObjects();

// Retrieve a copy of the 'star' that the player is standing on
STAR findStarAt(COORD pos);

// Retrieve a copy of the 'portal' that the player is standing on
PORTAL findPortalAt(COORD pos);

// Retrieve a copy of the 'trap' that the player is standing on
TRAP findTrapAt(COORD pos);

// Make all exits passable
void activateExit();

// Make all exits un-passable
void deactivateExit();

//generate random exit 
void randomExit();


#endif // !_INTERACTABLE_H