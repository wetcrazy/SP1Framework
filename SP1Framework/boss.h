#ifndef _BOSS_H
#define _BOSS_H

#include <Windows.h>

struct AI_BOSS {

	COORD pos;
	short health;
	short phase;

};



const WORD color_BOSS_SHIELD_ACTIVE_1 = 0x0C;
const WORD color_BOSS_SHIELD_INACTIVE = 0x08;


#endif