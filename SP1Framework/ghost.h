#ifndef _GHOST_H
#define _GHOST_H

#include <Windows.h>

struct AI_GHOST {

	unsigned int index;
	COORD pos;

};

const double movementSpeed_GHOST = 0.75; // Moves 1 character every X seconds


#endif