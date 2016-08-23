#ifndef _GHOST_H
#define _GHOST_H

#include <Windows.h>

struct AI_GHOST {

	unsigned int index;
	COORD pos;
	bool active;

};

const double movementSpeed_GHOST = 0.6; // Moves 1 character every X seconds
const short stun_GHOST_DURATION = 3;
const WORD color_GHOST_ACTIVE = 0x0C;
const WORD color_GHOST_INACTIVE = 0x08;


#endif