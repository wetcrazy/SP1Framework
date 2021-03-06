#ifndef _BULLETS_H
#define _BULLETS_H

#include "Framework\console.h"
#include "game.h"
#include "map.h"
#include "score.h"
#include "_interactable.h"
#include "_AI.h"

const WORD bulletPlayerColor = 0xF3;
const WORD bulletBossColor = 0xFC;

enum E_DIRECTION_BULLET {

	UP = 1,
	TOPRIGHT = 2,
	RIGHT = 3,
	BOTTOMRIGHT = 4,
	DOWN = 5,
	BOTTOMLEFT = 6,
	LEFT = 7,
	TOPLEFT = 8

};

struct BULLET {

	COORD pos;
	E_DIRECTION_BULLET direction;
	bool isPlayer;

};

// Spawn a bullet at the specific location and direction and if its owned by the player
void spawnBullet(COORD pos, E_DIRECTION_BULLET direction, bool isPlayer);

// Updates the logic for bullet
void updateBullets(double eTime, double dTime);

// Renders all bullets onto screen
void renderBullets(Console * handle, double eTime, double dTime);

// Removes the bullet with the specific index
void destroyBullet(vector<BULLET>::const_iterator i);

void destroyAllBullet();

#endif