#ifndef _AI_H
#define _AI_H

#include "map.h"
#include "ghost.h"
#include "game.h"


extern vector<AI_GHOST> _COLLECTION_AI_GHOST;

enum AI {

	GHOST = '@'

};


const char AI[] = {
	'@'
};


// Is this a non playable character?
bool isNPC(char c);

// Are the ghost stunned?
bool isGhostStunned();

// Stuns all ghost
void stunGhosts();

// Un-stuns all ghost
void unstunGhosts();

// Despawn all ghosts
void destroyGhosts();

// Destroy all AI objects
void destroyAI();

// Spawn the amount of ghosts at random location
void spawn_ghosts(unsigned int count);

// Repositions and process AI logic
void updateAI(double dTime);

// Renders AI onto the map
void renderAI(Console * handle);

#endif