#include "_interactable.h"
#include "game.h"
#include "map.h"
#include "score.h"

vector<STAR> _COLLECTION_OBJ_STAR;
vector<PORTAL> _COLLECTION_OBJ_PORTAL;
vector<EXIT> _COLLECTION_OBJ_EXIT;
vector<TRAP> _COLLECTION_OBJ_TRAP;
short _COLLECTION_OBJ_SHIELD_COUNT = 0;


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
	_COLLECTION_OBJ_TRAP.clear();
	_COLLECTION_OBJ_SHIELD_COUNT = 0;
}

// Object logic goes here
void updateObjects(Console * handle, MAP map, double eTime) {

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

			if (_POINTS_ASTERISK <= 0) {
				for (size_t i = 0; i < _COLLECTION_OBJ_EXIT.size(); i++) {

					COORD pos = _COLLECTION_OBJ_EXIT[i].pos;

					g_Map[pos.Y][pos.X] = I_EXIT_ACTIVE;

				}
			}

		}

		if (g_sChar.below == I_PORTAL) {

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

		if (g_sChar.below == I_TRAP) {

			static double stunReleaseTime = 0;

			TRAP trap = findTrapAt(g_sChar.m_cLocation);

			if (trap.active) {
				g_sChar.m_bStunned = true; // stun the player
				stunReleaseTime = eTime + _OBJ_TRAP_STUNTIME;
				_COLLECTION_OBJ_TRAP[trap.index].active = false;

			}
			else if (eTime >= stunReleaseTime) {
				g_sChar.m_bStunned = false;
				g_Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
				stunReleaseTime = 0;

			}

		}

		break;

	case LEVEL_THREE:
<<<<<<< HEAD
	case LEVEL_FOUR:

		if (g_sChar.below == ' ') {
			g_sChar.m_bActive = false;
		}

		if (g_sChar.below == I_STAR) {
			g_Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';

			if (_POINTS_ASTERISK > 0) {
				_POINTS_ASTERISK--; // Decrement stars left by 1
			}

			if (_POINTS_ASTERISK <= 0) {
				for (size_t i = 0; i < _COLLECTION_OBJ_EXIT.size(); i++) {

					COORD pos = _COLLECTION_OBJ_EXIT[i].pos;

					g_Map[pos.Y][pos.X] = I_EXIT_ACTIVE;

				}
=======
		if (g_sChar.below == I_TRAP) {

			static double stunReleaseTime = 0;

			TRAP trap = findTrapAt(g_sChar.m_cLocation);

			if (trap.active) {
				g_sChar.m_bStunned = true; // stun the player
				stunReleaseTime = eTime + _OBJ_TRAP_STUNTIME;
				_COLLECTION_OBJ_TRAP[trap.index].active = false;

			}
			else if (eTime >= stunReleaseTime) {
				g_sChar.m_bStunned = false;
				g_Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
				stunReleaseTime = 0;

			}

		}
		break;
	case LEVEL_FOUR:
		if (g_sChar.below == I_TRAP) {

			static double stunReleaseTime = 0;

			TRAP trap = findTrapAt(g_sChar.m_cLocation);

			if (trap.active) {
				g_sChar.m_bStunned = true; // stun the player
				stunReleaseTime = eTime + _OBJ_TRAP_STUNTIME;
				_COLLECTION_OBJ_TRAP[trap.index].active = false;

			}
			else if (eTime >= stunReleaseTime) {
				g_sChar.m_bStunned = false;
				g_Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
				stunReleaseTime = 0;

>>>>>>> 26d9b7c194ad6db686cc9f77f0687c91525fd7a9
			}

		}
		break;
	case LEVEL_FIVE:
		if (g_sChar.below == I_STAR) {
			g_Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';

			if (_POINTS_ASTERISK > 0) {
				_POINTS_ASTERISK--; // Decrement stars left by 1
			}
			
		}
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
