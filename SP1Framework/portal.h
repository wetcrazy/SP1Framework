#ifndef _PORTAL_H
#define _PORTAL_H

#include "Framework\console.h"



struct PORTAL {

	int index;
	COORD pos;
	bool active;

};

// Make all portals active again
void resetPortals();

#endif