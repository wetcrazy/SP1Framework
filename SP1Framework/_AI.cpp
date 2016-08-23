#include "_AI.h"




vector<AI_GHOST> _COLLECTION_AI_GHOST;


void stunGhosts() {
	for (unsigned int i = 0; i < _COLLECTION_AI_GHOST.size(); i++) {
		_COLLECTION_AI_GHOST[i].active = false;
	}
}

void unstunGhosts() {
	for (unsigned int i = 0; i < _COLLECTION_AI_GHOST.size(); i++) {
		_COLLECTION_AI_GHOST[i].active = true;
	}
}

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
	static double ghostDeltaStunned = 0;

	switch (current_level) {

	case LEVEL_ONE:
	case LEVEL_TWO:

		ghostDeltaMoved += dTime;

		// Ghost Stun recovering logic
		if (ghostDeltaStunned > 0) {
			ghostDeltaStunned += dTime;
			if (ghostDeltaStunned >= stun_GHOST_DURATION) {
				ghostDeltaStunned = 0;
				unstunGhosts();
				break;
			}
			return;
		}

		// Ghosts AI movement
		if (ghostDeltaMoved >= movementSpeed_GHOST) {

			for (unsigned int i = 0; i < _COLLECTION_AI_GHOST.size(); i++) {

				// Break if ghost is not active
				if (!_COLLECTION_AI_GHOST[i].active) {
					ghostDeltaStunned += dTime;
					return;
				}

				// Continue movement
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


				COORD ghostPos = _COLLECTION_AI_GHOST[i].pos;
				COORD playerPos = g_sChar.m_cLocation;

				if (ghostPos.X == playerPos.X && ghostPos.Y == playerPos.Y) {
					closeMap();
					LEVEL_restart = current_level;
					current_level = LEVEL_OVER;
					break;
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

	for (unsigned int i = 0; i < _COLLECTION_AI_GHOST.size(); i++) {

		WORD ghostColor = color_GHOST_ACTIVE;

		if (!_COLLECTION_AI_GHOST[i].active) {
			ghostColor = color_GHOST_INACTIVE;
		}

		handle->writeToBuffer(_COLLECTION_AI_GHOST[i].pos.X, _COLLECTION_AI_GHOST[i].pos.Y + header_offset, AI::GHOST, ghostColor);
	}

}

void destroyGhosts() {
	_COLLECTION_AI_GHOST.clear();
}

void destroyAI() {
	_COLLECTION_AI_GHOST.clear();
}