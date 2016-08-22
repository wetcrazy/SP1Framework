#include "_interactable.h"
#include "game.h"
#include "map.h"
#include "score.h"

vector<STAR> _COLLECTION_OBJ_STAR;
vector<PORTAL> _COLLECTION_OBJ_PORTAL;


// Test if the argument is an passable ASCII character
bool isPassable(char c) {
	for each (char ch in PASSABLES) {
		if (c == ch)
			return true;
	}
	return false;
}

// Test if the argument is an interactable object
bool isInteractable(char c) {
	for each (char ch in INTERACTABLES) {
		if (c == ch)
			return true;
	}
	return false;
}

void destroyObjects() {
	_COLLECTION_OBJ_STAR.clear();
	_COLLECTION_OBJ_PORTAL.clear();
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

		if (g_sChar.below == ' ') {
			g_sChar.m_bActive = false;
		}

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

			g_sChar.m_bActive = true;

			PORTAL port = findPortalAt(g_sChar.m_cLocation);

			// Is portal active?
			if (port.active) {

				// Reset all portals to active
				resetPortals();

				// Teleport to a random portal
				srand(time(NULL));
				int teleportIndex;

				// Keep randomizing if we get teleported to the same portal that we stepped on
				while ((teleportIndex = (rand() % _COLLECTION_OBJ_PORTAL.size())) == port.index) {
				}

				g_sChar.m_cLocation = _COLLECTION_OBJ_PORTAL[teleportIndex].pos;
				_COLLECTION_OBJ_PORTAL[teleportIndex].active = false;

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