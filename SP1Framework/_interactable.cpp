#include "_interactable.h"
#include "game.h"
#include "map.h"
#include "score.h"

vector<STAR> _COLLECTION_OBJ_STAR;
vector<PORTAL> _COLLECTION_OBJ_PORTAL;
vector<EXIT> _COLLECTION_OBJ_EXIT;


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
	_COLLECTION_OBJ_EXIT.clear();
}

// Object logic goes here
void updateObjects(Console * handle, MAP map) {

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

			if (_POINTS_ASTERISK > 0) {
				_POINTS_ASTERISK--; // Decrement stars left by 1
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

		if (_POINTS_ASTERISK <= 0) {
			for (size_t i = 0; i < _COLLECTION_OBJ_EXIT.size(); i++) {

				COORD pos = _COLLECTION_OBJ_EXIT[i].pos;

				g_Map[pos.Y][pos.X] = I_EXIT_ACTIVE;

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