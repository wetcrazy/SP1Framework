#include "_interactable.h"


PORTAL findPortalAt(COORD pos) {

	for (size_t i = 0; i < _COLLECTION_OBJ_PORTAL.size(); i++) {

		// If position matches, return current iterator
		if (_COLLECTION_OBJ_PORTAL[i].pos.X == pos.X && _COLLECTION_OBJ_PORTAL[i].pos.Y == pos.Y) {
			return _COLLECTION_OBJ_PORTAL[i];
		}

	}

	return PORTAL{};

}

void resetPortals() {

	for (unsigned int i = 0; i < _COLLECTION_OBJ_PORTAL.size(); i++) {
		_COLLECTION_OBJ_PORTAL[i].active = true;
	}

}