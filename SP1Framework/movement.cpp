#include "movement.h"


double g_dBounceTime = 0.0;
bool g_sCharCanMove = true;

void moveCharacter(Console * handle, double eTime, double dTime) {

	try {

		// Collision Detection
		g_sChar.c_Right = g_Map.at(g_sChar.m_cLocation.Y).at(g_sChar.m_cLocation.X + 1);
		g_sChar.c_Left = g_Map.at(g_sChar.m_cLocation.Y).at(g_sChar.m_cLocation.X - 1);
		g_sChar.c_Up = g_Map.at(g_sChar.m_cLocation.Y - 1).at(g_sChar.m_cLocation.X);
		g_sChar.c_Down = g_Map.at(g_sChar.m_cLocation.Y + 1).at(g_sChar.m_cLocation.X);

		g_sChar.c_TopRight = g_Map.at(g_sChar.m_cLocation.Y - 1).at(g_sChar.m_cLocation.X + 1);
		g_sChar.c_TopLeft = g_Map.at(g_sChar.m_cLocation.Y - 1).at(g_sChar.m_cLocation.X - 1);
		g_sChar.c_BottomLeft = g_Map.at(g_sChar.m_cLocation.Y + 1).at(g_sChar.m_cLocation.X - 1);
		g_sChar.c_BottomRight = g_Map.at(g_sChar.m_cLocation.Y + 1).at(g_sChar.m_cLocation.X + 1);

		g_sChar.c_Below = g_Map.at(g_sChar.m_cLocation.Y).at(g_sChar.m_cLocation.X);

	}

	// am i going to hell for this? D:
	catch (out_of_range ex) {

		closeMap();

		switch (current_level) {

		case LEVEL_ONE:
			current_level = LEVEL_TWO;
			break;
		case LEVEL_TWO:
			current_level = LEVEL_THREE;
			break;
		case LEVEL_THREE:
			current_level = LEVEL_FIVE;
			break;
		default:
			current_level = LEVEL_TITLE;
			break;
		}

	}

	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;

	if (!g_sChar.m_bStunned) {

		// Detecting 8 different possible key combination then move the player
		if (!g_abKeyPressed[K_DOWN] && !g_abKeyPressed[K_RIGHT] && g_abKeyPressed[K_LEFT] && g_abKeyPressed[K_UP] && g_sChar.m_cLocation.X > 0 && isPassable(g_sChar.c_TopLeft)) {
			g_sChar.m_cLocation.X--;
			g_sChar.m_cLocation.Y--;
			bSomethingHappened = true;
		}
		else if (!g_abKeyPressed[K_DOWN] && !g_abKeyPressed[K_LEFT] && g_abKeyPressed[K_RIGHT] && g_abKeyPressed[K_UP] && g_sChar.m_cLocation.X > 0 && isPassable(g_sChar.c_TopRight)) {
			g_sChar.m_cLocation.X++;
			g_sChar.m_cLocation.Y--;
			bSomethingHappened = true;
		}
		else if (!g_abKeyPressed[K_RIGHT] && !g_abKeyPressed[K_UP] && g_abKeyPressed[K_LEFT] && g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < handle->getConsoleSize().Y - 1 && isPassable(g_sChar.c_BottomLeft)) {
			g_sChar.m_cLocation.X--;
			g_sChar.m_cLocation.Y++;
			bSomethingHappened = true;
		}
		else if (!g_abKeyPressed[K_LEFT] && !g_abKeyPressed[K_UP] && g_abKeyPressed[K_RIGHT] && g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < handle->getConsoleSize().Y - 1 && isPassable(g_sChar.c_BottomRight)) {
			g_sChar.m_cLocation.X++;
			g_sChar.m_cLocation.Y++;
			bSomethingHappened = true;
		}
		else if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 0 && isPassable(g_sChar.c_Up)) {
			g_sChar.m_cLocation.Y--;
			bSomethingHappened = true;
		}
		else if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0 && isPassable(g_sChar.c_Left)) {
			g_sChar.m_cLocation.X--;
			bSomethingHappened = true;
		}
		else if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < handle->getConsoleSize().Y - 1 && isPassable(g_sChar.c_Down)) {
			g_sChar.m_cLocation.Y++;
			bSomethingHappened = true;
		}
		else if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < handle->getConsoleSize().X - 1 && isPassable(g_sChar.c_Right)) {
			g_sChar.m_cLocation.X++;
			bSomethingHappened = true;
		}

	}

	if (bSomethingHappened) {
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.1;
	}


}