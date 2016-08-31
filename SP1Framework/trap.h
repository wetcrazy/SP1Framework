#ifndef _TRAP_H
#define _TRAP_H

#include "Framework\console.h"

const double _OBJ_TRAP_STUNTIME = 4.0;

struct TRAP {

	int index;
	COORD pos;
	bool active;

};


const WORD _OBJ_TRAP_COLOR = 0xFC;

#endif