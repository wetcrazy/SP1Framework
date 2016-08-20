#include "_interactable.h"



STAR findStarAt(COORD pos) {

	for (size_t i = 0; i < _COLLECTION_OBJ_STAR.size(); i++) {

		// If position matches, return current iterator
		if (_COLLECTION_OBJ_STAR[i].pos.X == pos.X && _COLLECTION_OBJ_STAR[i].pos.Y == pos.Y) {
			return _COLLECTION_OBJ_STAR[i];
		}

	}

	return STAR{};

}