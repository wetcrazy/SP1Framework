#ifndef _BOSS_H
#define _BOSS_H

#include "Framework\console.h"

struct AI_BOSS {

	COORD pos;
	short health;
	short phase;
	bool stunned;

};

const WORD color_BOSS_SHIELD_ACTIVE_1 = 0x0C;
const WORD color_BOSS_SHIELD_INACTIVE = 0x08;
const WORD color_BOSS_STUNNED = 0x5F;

const WORD color_BOSS_P1_COLOR = 0xF0;
const WORD color_BOSS_P2_COLOR = 0xFC;
const WORD color_BOSS_P3_COLOR = 0xC0;

const short boss_HEALTH_DEFAULT = 50;
const short boss_HEALTH_DEFAULT_P3 = 50;
const double boss_STUN_DURATION = 3;



#endif