#ifndef _GHOST_H
#define _GHOST_H

#include <Windows.h>

struct AI_GHOST {

	unsigned int index;
	COORD pos;
	char  xP;
	char  xN;
	char  yP;
	char  yN;
	char  below;

};


#endif