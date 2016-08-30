#ifndef _AI_H
#define _AI_H

#include "map.h"
#include "ghost.h"
#include "game.h"
#include "boss.h"
#include "score.h"
#include "gameUtils.h"
#include <random>

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

// Set all ghosts in the vector to 'inactive'
void stunGhosts();

// Set all ghosts in the vector to 'active'
void unstunGhosts();

// Despawn all ghosts
void destroyGhosts();

// Despawn the passed ghost
void destroyGhost(vector<AI_GHOST>::const_iterator i);

// Destroy all AI objects
void destroyAI();

// Spawn ghost at specific coordinates
void spawn_ghost(COORD pos, bool active);

// Not really spawning but initializing the boss's struct
void spawn_boss(COORD pos);

// Reset the static variables for the boss
void resetBoss();

// Sets the 'stunned' property in boss struct to true, duration denoted in boss.h
void stunBoss();

// Sets the 'stunned' property in boss struct to false
void unstunBoss();

// Moves the boss to the specific coordinates
void moveBossTo(COORD dest, double eTime, double dTime);

// Processes ghost ai logic
void updateGhostMovement(double eTime, double dTime);

// Process Ghost touch logic, returns true if player is touched
bool updateGhostTouch();

// Repositions and process AI logic
void updateAI(double eTime,double dTime);

// Renders AI onto the map
void renderAI(Console * handle);

#endif