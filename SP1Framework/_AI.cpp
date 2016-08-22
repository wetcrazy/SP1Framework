#include "_AI.h"




vector<AI_GHOST> _COLLECTION_AI_GHOST;




bool isNPC(char c) {
	for each (char it in AI) {
		if (c == it) {
			return true;
		}
	}
	return false;
}

void updateAI(double dTime) {

	static double ghostDeltaMoved = 0;

	switch (current_level) {

	case LEVEL_ONE:
	case LEVEL_TWO:

		ghostDeltaMoved += dTime;

		// Ghosts
		if (ghostDeltaMoved >= movementSpeed_GHOST) {

			for (unsigned int i = 0; i < _COLLECTION_AI_GHOST.size(); i++) {

				if (_COLLECTION_AI_GHOST[i].pos.X > g_sChar.m_cLocation.X) {
					_COLLECTION_AI_GHOST[i].pos.X--;
				}
				else if (_COLLECTION_AI_GHOST[i].pos.X < g_sChar.m_cLocation.X) {
					_COLLECTION_AI_GHOST[i].pos.X++;
				}

				if (_COLLECTION_AI_GHOST[i].pos.Y > g_sChar.m_cLocation.Y) {
					_COLLECTION_AI_GHOST[i].pos.Y--;
				}

				else if (_COLLECTION_AI_GHOST[i].pos.Y < g_sChar.m_cLocation.Y) {
					_COLLECTION_AI_GHOST[i].pos.Y++;
				}

			}
			ghostDeltaMoved = 0;
		}

		break;

	case LEVEL_THREE:
		// Boss AI Here
		break;

	}



}


void renderAI(Console * handle) {

	WORD ghostColor = 0xFC;

	for (unsigned int i = 0; i < _COLLECTION_AI_GHOST.size(); i++) {
		handle->writeToBuffer(_COLLECTION_AI_GHOST[i].pos.X, _COLLECTION_AI_GHOST[i].pos.Y + header_offset, AI::GHOST, ghostColor);
	}

}

void destroyGhosts() {
	_COLLECTION_AI_GHOST.clear();
}