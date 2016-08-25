#ifndef _AI_H
#define _AI_H

#include "map.h"
#include "ghost.h"
#include "game.h"
#include "boss.h"
#include "score.h"


extern vector<AI_GHOST> _COLLECTION_AI_GHOST;
extern AI_BOSS _AI_BOSS;

enum AI {

	GHOST = '@',
	BOSS = '&'

};


const char AI[] = {
	GHOST,
	BOSS
};


// Is this a non playable character?
bool isNPC(char c);

// Are the ghost stunned?
bool isGhostStunned();

// Are there any ghost in this position? Skips iteration of index 'i'
bool isGhostAtPos(int i, COORD pos);

// Checks the boss hp bar
void HurtBoss();

// Stuns all ghost
void stunGhosts();

// Un-stuns all ghost
void unstunGhosts();

// Despawn all ghosts
void destroyGhosts();

// Destroy all AI objects
void destroyAI();

// Spawn ghost at specific coordinates
void spawn_ghosts(COORD pos);

// Not really spawning but initializing the boss's struct
void spawn_boss(COORD pos);

// Repositions and process AI logic
void updateAI(double eTime,double dTime);

// Renders AI onto the map
void renderAI(Console * handle);

#endif