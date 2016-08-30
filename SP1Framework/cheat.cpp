#include "cheat.h"
#include "Map.h"
#include "game.h"

bool b_CheatEnabled = false;

void processcheat(bool *g_abKeyPressed) {

	if (isKeyPressed(_CHEAT_HOTKEY)) {
		b_CheatEnabled = true;
	}

	if (b_CheatEnabled) {

		if (g_abKeyPressed[K_F1]) {
			closeMap();
			current_level = LEVEL_ONE;
		}
		else if (g_abKeyPressed[K_F2]) {
			closeMap();
			current_level = LEVEL_TWO;

		}
		else if (g_abKeyPressed[K_F3]) {
			closeMap();
			current_level = LEVEL_THREE;

		}
		else if (g_abKeyPressed[K_F4]) {
			closeMap();
			current_level = LEVEL_FOUR;

		}
		else if (g_abKeyPressed[K_F5]) {
			closeMap();
			current_level = LEVEL_FIVE;

		}

	}

}


