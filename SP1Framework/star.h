#ifndef _STAR_H
#define _STAR_H


#include "_interactable.h"


struct STAR {

	COORD pos;
	void interact() {

		if (isKeyPressed(VK_SPACE)) {

		}

	}

};


// Star spawns
const COORD _SPAWN_STAR[10] = {

	{ 1, 1 },


};

#endif // !1