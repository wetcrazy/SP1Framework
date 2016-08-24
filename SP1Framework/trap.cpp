#include "_interactable.h"



TRAP findTrapAt(COORD pos) {

	for (size_t i = 0; i < _COLLECTION_OBJ_TRAP.size(); i++) {

		// If position matches, return current iterator
		if (_COLLECTION_OBJ_TRAP[i].pos.X == pos.X && _COLLECTION_OBJ_TRAP[i].pos.Y == pos.Y) {
			return _COLLECTION_OBJ_TRAP[i];
		}

	}

	return TRAP{};

}