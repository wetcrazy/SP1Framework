#ifndef _GHOST_H
#define _GHOST_H

#include <Windows.h>

struct AI_GHOST {

	unsigned int index;
	COORD pos;
	bool active;

};

// Moves 1 character every X seconds, lower this to increase speed
extern double movementSpeed_GHOST; 

const short stun_GHOST_DURATION = 3;
const WORD color_GHOST_ACTIVE = 0x0C;
const WORD color_GHOST_INACTIVE = 0x08;


#endif