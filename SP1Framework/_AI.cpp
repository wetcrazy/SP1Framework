#include "_AI.h"
#include "_interactable.h"



vector<AI_GHOST> _COLLECTION_AI_GHOST;
AI_BOSS _AI_BOSS;

bool isGStunned = false;


void stunGhosts() {
	for (unsigned int i = 0; i < _COLLECTION_AI_GHOST.size(); i++) {
		_COLLECTION_AI_GHOST[i].active = false;
	}
}

void HurtBoss()
{
	//if boss is hurt, reduce it's hp bar
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

bool isGhostStunned(){
	return isGStunned;
}

bool isGhostAtPos(int i, COORD pos){

	for each (AI_GHOST g in _COLLECTION_AI_GHOST){
		if (g.pos.X == pos.X && g.pos.Y == pos.Y && g.index != i){
			return true;
		}
	}
	return false;
}

void updateAI(double eTime, double dTime) {

	static double ghostDeltaMoved = 0;
	static double ghostDeltaStunned = 0;

	switch (current_level) {

	case LEVEL_ONE:
	case LEVEL_TWO:

		ghostDeltaMoved += dTime;

		// Ghost Stun recovering logic
		if (ghostDeltaStunned > 0) {
			isGStunned = true;
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

			isGStunned = false;

			for (unsigned int i = 0; i < _COLLECTION_AI_GHOST.size(); i++) {

				// Break if ghost is not active
				if (!_COLLECTION_AI_GHOST[i].active) {
					ghostDeltaStunned += dTime;
					return;
				}

				COORD tempPos;

				// Continue movement
				if (_COLLECTION_AI_GHOST[i].pos.X > g_sChar.m_cLocation.X) {

					tempPos = _COLLECTION_AI_GHOST[i].pos;
					tempPos.X--;

					// Dont move if we are going to collide into another ghost
					if (!isGhostAtPos(i, tempPos)){
						_COLLECTION_AI_GHOST[i].pos.X--;
					}

				}
				else if (_COLLECTION_AI_GHOST[i].pos.X < g_sChar.m_cLocation.X) {

					tempPos = _COLLECTION_AI_GHOST[i].pos;
					tempPos.X++;

					// Dont move if we are going to collide into another ghost
					if (!isGhostAtPos(i, tempPos)){
						_COLLECTION_AI_GHOST[i].pos.X++;
					}
				}

				if (_COLLECTION_AI_GHOST[i].pos.Y > g_sChar.m_cLocation.Y) {

					tempPos = _COLLECTION_AI_GHOST[i].pos;
					tempPos.Y--;

					// Dont move if we are going to collide into another ghost
					if (!isGhostAtPos(i, tempPos)){
						_COLLECTION_AI_GHOST[i].pos.Y--;
					}
				}

				else if (_COLLECTION_AI_GHOST[i].pos.Y < g_sChar.m_cLocation.Y) {

					tempPos = _COLLECTION_AI_GHOST[i].pos;
					tempPos.Y++;

					// Dont move if we are going to collide into another ghost
					if (!isGhostAtPos(i, tempPos)){
						_COLLECTION_AI_GHOST[i].pos.Y++;
					}
				}

			}
			ghostDeltaMoved = 0;

		}

		// Did player touched a ghost?
		for (unsigned int i = 0; i < _COLLECTION_AI_GHOST.size(); i++){

			COORD ghostPos = _COLLECTION_AI_GHOST[i].pos;
			COORD playerPos = g_sChar.m_cLocation;

			if (ghostPos.X == playerPos.X && ghostPos.Y == playerPos.Y) {
				closeMap();
				LEVEL_restart = current_level;
				current_level = LEVEL_OVER;
				break;
			}
		}

		break;

	case LEVEL_THREE:
	case LEVEL_FOUR:

		break;

	case LEVEL_FIVE: // Boss AI Logic

		// Different phases logic for Boss
		switch (_AI_BOSS.phase){

		case 1: // P1

			// Transition to phase 2 when enough stars are collected
			if (_POINTS_ASTERISK <= 0){
				if (_COLLECTION_OBJ_SHIELD_COUNT > 0){
					replaceMapCharacter(I_SHIELD, ' ');
					_COLLECTION_OBJ_SHIELD_COUNT--;

					if (_COLLECTION_OBJ_SHIELD_COUNT <= 0){
						_AI_BOSS.phase = 2;
					}
				}
			}

			// TODO: Boss attacking Logic

			break;

		case 2: // P2



			break;

		case 3: // P3

			break;

		}


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

void spawn_boss(COORD pos){

	_AI_BOSS.pos = pos;
	_AI_BOSS.health = 15;
	_AI_BOSS.phase = 1;

}