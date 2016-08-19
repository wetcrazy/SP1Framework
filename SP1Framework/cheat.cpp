#include "cheat.h"
#include "Map.h"
#include "game.h"

void processcheat( double  g_dBounceTime, double  g_dElapsedTime, bool g_abKeyPressed[K_COUNT])
{
	bool bSomethingHappened = false;
	
	if (g_dBounceTime > g_dElapsedTime)
		return;
	if (g_abKeyPressed[K_F1] ) {
		closeMap();
		current_level = LEVEL_TITLE;
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_F2] ) {
		closeMap;
		current_level = LEVEL_TWO;
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_F3]) {
		closeMap;
		current_level =LEVEL_THREE;
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_F4]) {
		closeMap;
		current_level = LEVEL_FOUR;
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_F5]) {
		closeMap;
		current_level = LEVEL_FIVE;
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_F6]) {
		closeMap;
		current_level = LEVEL_SIX;
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_F7]) {
		closeMap;
		current_level = LEVEL_SEVEN;
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_F8]) {
		closeMap;
		current_level = LEVEL_EIGHT;
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_F9]) {
		closeMap;
		current_level = LEVEL_NINE;
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_F10]) {
		closeMap;
		current_level = LEVEL_TEN;
		bSomethingHappened = true;
	}
	if (bSomethingHappened) {
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.1; // 125ms should be enough
	}
}


