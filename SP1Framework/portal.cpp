#include "_interactable.h"


PORTAL findPortalAt(COORD pos) {

	for (size_t i = 0; i < _OBJ_COLLECTION_PORTAL.size(); i++) {

		// If position matches, return current iterator
		if (_OBJ_COLLECTION_PORTAL[i].pos.X == pos.X && _OBJ_COLLECTION_PORTAL[i].pos.Y == pos.Y) {
			return _OBJ_COLLECTION_PORTAL[i];
		}

	}

	return PORTAL{};

}

void resetPortals() {

	for (int i = 0; i < _OBJ_COLLECTION_PORTAL.size(); i++) {
		_OBJ_COLLECTION_PORTAL[i].active = true;
	}

}