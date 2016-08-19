#include "cheat.h"
#include "Map.h"
#include "game.h"

void processcheat(  bool *g_abKeyPressed)
{
	
	if (g_abKeyPressed[K_F1] ) {
		closeMap();
		current_level = LEVEL_ONE;
	}
	else if (g_abKeyPressed[K_F2] ) {
		closeMap();
		current_level = LEVEL_TWO;
		
	}
	else if (g_abKeyPressed[K_F3]) {
		closeMap();
		current_level =LEVEL_THREE;
		
	}
	else if (g_abKeyPressed[K_F4]) {
		closeMap();
		current_level = LEVEL_FOUR;
		
	}
	else if (g_abKeyPressed[K_F5]) {
		closeMap();
		current_level = LEVEL_FIVE;
		
	}
	else if (g_abKeyPressed[K_F6]) {
		closeMap();
		current_level = LEVEL_SIX;
		
	}
	else if (g_abKeyPressed[K_F7]) {
		closeMap();
		current_level = LEVEL_SEVEN;
		
	}
	else if (g_abKeyPressed[K_F8]) {
		closeMap();
		current_level = LEVEL_EIGHT;
		
	}
	else if (g_abKeyPressed[K_F9]) {
		closeMap();
		current_level = LEVEL_NINE;
		
	}
	else if (g_abKeyPressed[K_F10]) {
		closeMap();
		current_level = LEVEL_TEN;
		
	}
}


