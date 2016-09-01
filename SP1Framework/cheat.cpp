#include "cheat.h"
#include "Map.h"
#include "game.h"

bool b_CheatEnabled = false;
extern bool Cheat_FPS;

void processcheat(bool *g_abKeyPressed) {

	if (isKeyPressed(_CHEAT_HOTKEY)) {
		b_CheatEnabled = true;
	}

	if (b_CheatEnabled) {
		
		// Skip to Level One 
		if (g_abKeyPressed[K_F1]) {
			closeMap();
			current_level = LEVEL_ONE;
			_AI_BOSS.phase = 0;
		}
		// Skip to level two
		else if (g_abKeyPressed[K_F2]) {
			closeMap();
			current_level = LEVEL_TWO;
			_AI_BOSS.phase = 0;
		}
		// Skip to Level Three
		else if (g_abKeyPressed[K_F3]) {
			closeMap();
			current_level = LEVEL_THREE;
			_AI_BOSS.phase = 0;
		}
		// Skip to Level Four 
		else if (g_abKeyPressed[K_F4]) {
			closeMap();
			current_level = LEVEL_FOUR;
			_AI_BOSS.phase = 0;
		}
		// Skip to Level Five
		else if (g_abKeyPressed[K_F5]) {
			closeMap();
			current_level = LEVEL_FIVE;

		}
		// Skip to Winning Screen
		else if (g_abKeyPressed[K_F6]) {
			closeMap();
			current_level = LEVEL_WON;

		}
		// Reduce Star Count to One
		else if (g_abKeyPressed[K_F9])
		{
			_POINTS_ASTERISK = 1;
		}
		// Reduce Boss Health to One
		else if (g_abKeyPressed[K_F10])
		{
			_AI_BOSS.health = 1;
		}
		// Disable FPS and Timer
		else if (g_abKeyPressed[K_F11])
		{
			Cheat_FPS = false;
		}
		else if (g_abKeyPressed[k_F12])
		{
			Cheat_FPS = true;
		}
	}

}


