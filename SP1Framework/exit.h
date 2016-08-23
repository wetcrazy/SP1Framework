#ifndef _EXIT_H
#define _EXIT_H

#include "Framework\console.h"



struct EXIT {

	COORD pos;
	bool active;

};

const WORD _OBJECT_EXIT_COLOR_ACTIVE = 0x1F;
const WORD _OBJECT_EXIT_COLOR_INACTIVE = 0xDF;


#endif 