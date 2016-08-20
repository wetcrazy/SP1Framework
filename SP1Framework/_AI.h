#ifndef _AI_H
#define _AI_H

#include "map.h"
#include "ghost.h"


extern vector<AI_GHOST> _COLLECTION_AI_GHOST;

enum AI {

	GHOST = '@'

};






// Despawn all ghosts
void destroy_ghosts();

// Spawn the amount of ghosts at random location
void spawn_ghosts(unsigned int count);

// Repositions and process AI logic
void updateAI();

#endif