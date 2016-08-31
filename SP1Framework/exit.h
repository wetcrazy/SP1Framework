#ifndef _EXIT_H
#define _EXIT_H

#include "Framework\console.h"


struct EXIT {

	COORD pos;
	bool active;

};

const WORD _OBJ_EXIT_COLOR_ACTIVE = 0x9F;
const WORD _OBJ_EXIT_COLOR_INACTIVE = 0xFC;


#endif 