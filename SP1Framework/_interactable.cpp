#include "_interactable.h"
#include "game.h"
#include "map.h"
#include "score.h"

vector<STAR> _OBJ_COLLECTION_STAR;
vector<PORTAL> _OBJ_COLLECTION_PORTAL;


// Test if the argument is a passable ASCII character
bool isPassable(char c) {
	for each (char ch in PASSABLES) {
		if (c == ch)
			return true;
	}
	return false;
}

bool isInteractable(char c) {
	for each (char ch in INTERACTABLES) {
		if (c == ch)
			return true;
	}
	return false;
}


// Object logic goes here
void updateObjects(MAP map) {

	switch (map) {
	case LEVEL_TITLE:
		break;
	case LEVEL_MENU:
		break;

	case LEVEL_ONE:
	case LEVEL_TWO:

		if (g_sChar.below == I_STAR) {
			g_Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
			_POINTS_ASTERISK--;

			// If all stars are collected, open the gate
			if (_POINTS_ASTERISK <= 0) {
				for (size_t r = 0; r < g_Map.size(); r++) {

					for (size_t c = 0; c < g_Map[r].size(); c++) {
						if (g_Map[r][c] == '#') {
							g_Map[r][c] = ' ';
						}
					}

				}
			}

		}

		if (g_sChar.below == I_PORTAL) {

			// Is portal active?
			if (findPortalAt(g_sChar.m_cLocation).active) {

				// Reset all portals to active
				resetPortals();

				// Teleport to a random portal at a 50% chance
				srand(time(NULL));
				int portalIndex = (rand() % _OBJ_COLLECTION_PORTAL.size());
				g_sChar.m_cLocation = _OBJ_COLLECTION_PORTAL[portalIndex].pos;
				_OBJ_COLLECTION_PORTAL[portalIndex].active = false;
				// TODO: Change player color on teleport!

			}

		}

		break;

	case LEVEL_THREE:
		break;
	case LEVEL_FOUR:
		break;
	case LEVEL_FIVE:
		break;
	case LEVEL_SIX:
		break;
	case LEVEL_SEVEN:
		break;
	case LEVEL_EIGHT:
		break;
	case LEVEL_NINE:
		break;
	case LEVEL_TEN:
		break;
	}


}