#ifndef _PORTAL_H
#define _PORTAL_H

#include "Framework\console.h"

const WORD _OBJ_PORTAL_COLOR = 0xAF;

struct PORTAL {

	int index;
	COORD pos;
	bool active;

};

// Make all portals active again
void resetPortals();

#endif