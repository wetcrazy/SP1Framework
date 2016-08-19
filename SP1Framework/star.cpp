#include "_interactable.h"



STAR findStarAt(COORD pos) {

	for (size_t i = 0; i < _OBJ_COLLECTION_STAR.size(); i++) {

		// If position matches, return current iterator
		if (_OBJ_COLLECTION_STAR[i].pos.X == pos.X && _OBJ_COLLECTION_STAR[i].pos.Y == pos.Y) {
			return _OBJ_COLLECTION_STAR[i];
		}

	}

	return STAR{};

}