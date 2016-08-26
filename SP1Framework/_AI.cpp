#include "_AI.h"
#include "_interactable.h"



vector<AI_GHOST> _COLLECTION_AI_GHOST;
AI_BOSS _AI_BOSS;
double movementSpeed_GHOST = 0.6;
bool isGStunned = false;


void stunGhosts() {
	for (unsigned int i = 0; i < _COLLECTION_AI_GHOST.size(); i++) {
		_COLLECTION_AI_GHOST[i].active = false;
	}
}

void unstunGhosts() {
	isGStunned = false;
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

bool isGhostStunned() {
	return isGStunned;
}

bool isGhostAtPos(int i, COORD pos) {

	for each (AI_GHOST g in _COLLECTION_AI_GHOST) {
		if (g.pos.X == pos.X && g.pos.Y == pos.Y && g.index != i) {
			return true;
		}
	}
	return false;
}

void updateAI(double eTime, double dTime) {

	switch (current_level) {

	case LEVEL_ONE:
	case LEVEL_TWO:
	case LEVEL_THREE:
	case LEVEL_FOUR:
		movementSpeed_GHOST = 0.6;
		updateGhostMovement(eTime, dTime);
		updateGhostTouch();
		break;

	case LEVEL_FIVE: // Boss AI Logic

		// Clumsy ghost spawning animation
		static bool transitioned1 = false;
		static int ghostIndex = 0;
		static double nextSpawnTime = eTime;
		const double spawnInterval = 1;
		const short ghostSpawnRadiusX = 5;
		const short ghostSpawnRadiusY = 4;
		movementSpeed_GHOST = 0.2; // increase movespeed of ghosts

		// Logics for all Boss phases
		switch (_AI_BOSS.phase) {

		case 1: // P1

			// Spawn 4 ghosts upon entering this stage
			if (!transitioned1 && !isKeyPressed(VK_F5) && eTime >= nextSpawnTime) {

				g_sChar.m_bStunned = true; // stop the player from moving first

				COORD ghost_pos;

				switch (ghostIndex) {

				case 0:
					ghost_pos.X = _AI_BOSS.pos.X - ghostSpawnRadiusX;
					ghost_pos.Y = _AI_BOSS.pos.Y - ghostSpawnRadiusY;
					spawn_ghost(ghost_pos, false);
					ghostIndex++;
					nextSpawnTime = eTime + spawnInterval;
					break;

				case 1:
					ghost_pos.X = _AI_BOSS.pos.X + ghostSpawnRadiusX;
					ghost_pos.Y = _AI_BOSS.pos.Y - ghostSpawnRadiusY;
					spawn_ghost(ghost_pos, false);
					nextSpawnTime = eTime + spawnInterval;
					ghostIndex++;
					break;

				case 2:
					ghost_pos.X = _AI_BOSS.pos.X - ghostSpawnRadiusX;
					ghost_pos.Y = _AI_BOSS.pos.Y + ghostSpawnRadiusY;
					spawn_ghost(ghost_pos, false);
					nextSpawnTime = eTime + spawnInterval;
					ghostIndex++;
					break;

				case 3:
					ghost_pos.X = _AI_BOSS.pos.X + ghostSpawnRadiusX;
					ghost_pos.Y = _AI_BOSS.pos.Y + ghostSpawnRadiusY;
					spawn_ghost(ghost_pos, false);
					nextSpawnTime = eTime + spawnInterval;
					ghostIndex++;
					break;

				case 4:
					unstunGhosts(); // activate all the ghosts
					g_sChar.m_bStunned = false; // resume movement after animation
					transitioned1 = true;
					break;

				}

			}

			// Animation done, start moving the ghost
			if (transitioned1) {
				updateGhostMovement(eTime, dTime);
				if (updateGhostTouch()) {
					transitioned1 = false;
					ghostIndex = 0;
					nextSpawnTime = eTime;
				}
			}

			// Transition to phase 2 when enough stars are collected
			if (_POINTS_ASTERISK <= 0) {
				if (_COLLECTION_OBJ_SHIELD_COUNT > 0) {
					replaceMapCharacter(I_SHIELD, ' ');
					_COLLECTION_OBJ_SHIELD_COUNT--;

					if (_COLLECTION_OBJ_SHIELD_COUNT <= 0) {
						_AI_BOSS.phase = 2; // Shields removed, proceed to phase 2
					}
				}
			}

			break;

		case 2: // P2

			// Boss attacking logic
			// 1: Moves left & right and shoots projectile @ up, down, left, right, diagonally
			// 2: To damage boss: 
			break;

		case 3: // P3

			break;

		}

		break;

	}

}


// Did player touched a ghost?
bool updateGhostTouch() {
	for (unsigned int i = 0; i < _COLLECTION_AI_GHOST.size(); i++) {

		COORD ghostPos = _COLLECTION_AI_GHOST[i].pos;
		COORD playerPos = g_sChar.m_cLocation;

		if (ghostPos.X == playerPos.X && ghostPos.Y == playerPos.Y) {
			closeMap();
			LEVEL_restart = current_level;
			current_level = LEVEL_OVER;
			return true;
		}
	}
	return false;
}

void updateGhostMovement(double eTime, double dTime) {

	static double ghostDeltaMoved = 0;
	static double ghostDeltaStunned = 0;

	ghostDeltaMoved += dTime;

	// Ghost Stun recovering logic
	if (ghostDeltaStunned > 0) {
		isGStunned = true;
		ghostDeltaStunned += dTime;
		if (ghostDeltaStunned >= stun_GHOST_DURATION) {
			ghostDeltaStunned = 0;
			unstunGhosts();
			//break;
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
				if (!isGhostAtPos(i, tempPos)) {
					_COLLECTION_AI_GHOST[i].pos.X--;
				}

			}
			else if (_COLLECTION_AI_GHOST[i].pos.X < g_sChar.m_cLocation.X) {

				tempPos = _COLLECTION_AI_GHOST[i].pos;
				tempPos.X++;

				// Dont move if we are going to collide into another ghost
				if (!isGhostAtPos(i, tempPos)) {
					_COLLECTION_AI_GHOST[i].pos.X++;
				}
			}

			if (_COLLECTION_AI_GHOST[i].pos.Y > g_sChar.m_cLocation.Y) {

				tempPos = _COLLECTION_AI_GHOST[i].pos;
				tempPos.Y--;

				// Dont move if we are going to collide into another ghost
				if (!isGhostAtPos(i, tempPos)) {
					_COLLECTION_AI_GHOST[i].pos.Y--;
				}
			}

			else if (_COLLECTION_AI_GHOST[i].pos.Y < g_sChar.m_cLocation.Y) {

				tempPos = _COLLECTION_AI_GHOST[i].pos;
				tempPos.Y++;

				// Dont move if we are going to collide into another ghost
				if (!isGhostAtPos(i, tempPos)) {
					_COLLECTION_AI_GHOST[i].pos.Y++;
				}
			}

		}
		ghostDeltaMoved = 0;

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

void spawn_ghost(COORD pos, bool active) {
	_COLLECTION_AI_GHOST.push_back(AI_GHOST{
		_COLLECTION_AI_GHOST.size(), pos, active
	});
}

void spawn_boss(COORD pos) {

	_AI_BOSS.pos = pos;
	_AI_BOSS.health = 15;
	_AI_BOSS.phase = 1;

}