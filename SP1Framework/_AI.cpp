#include "_AI.h"
#include "_interactable.h"
#include "bullet.h"




vector<AI_GHOST> _COLLECTION_AI_GHOST;
AI_BOSS _AI_BOSS;
double movementSpeed_GHOST = 0.6;
bool isGStunned = false;

// Boss Phase 1
static double nextSpawnTime = 0.0;
static bool transitioned1 = false;
static int ghostIndex = 0;
const double spawnInterval = 1; // Clumsy ghost spawning animation
const short ghostSpawnRadiusX = 5;
const short ghostSpawnRadiusY = 4;

// Boss Phase 2
const double bossP2MoveInterval = 2; // Moves to a new location every X seconds
const double bossP2ShootInterval = 0.10; // Shoots a bullet every X seconds
const short  bossP2StunInterval = 3;  // Stuns the boss after moving X amount of times
const double bossP2StunDuration = 5; // How long will the boss be stunned for
static COORD bossP2locationToMove = getRandomMapLocation();
static double bossP2nextMoveTime = 0.0;
static double bossP2nextShootTime = bossP2ShootInterval;
static short bossP2movesBeforeStunned = bossP2StunInterval;

// Boss Phase 3
const double bossP3MoveInterval = 0.08; // Interval before boss moves to the next location
const double bossP3ShootInterval = 0.05; // Shoots a bullet every X seconds
const double bossP3StunDuration = 3; // How long will the boss be stunned for
const double bossP3DirectionChangeInterval = 1.5;
const COORD bossP3location1 = COORD{ 1, 1 };
COORD bossP3location2;
COORD bossP3location3;
static double bossP3nextMoveTime = bossP3MoveInterval;
static double bossP3nextShootTime = bossP3ShootInterval;
static double bossP3nextDirectionChange = bossP3DirectionChangeInterval;
static short bossP3Stage = 0;
static bool movingLeft = false;
static E_DIRECTION_BULLET direction1 = UP;
static E_DIRECTION_BULLET direction2 = RIGHT;
static E_DIRECTION_BULLET direction3 = DOWN;
static E_DIRECTION_BULLET direction4 = LEFT;

// Boss Ending Phase
COORD bossP4location;


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
		movementSpeed_GHOST = 0.45;
		updateGhostMovement(eTime, dTime);
		if (!isGhostStunned()) {
			updateGhostTouch();
		}
		break;
	case LEVEL_TWO:
		movementSpeed_GHOST = 0.45;
		updateGhostMovement(eTime, dTime);
		if (!isGhostStunned()) {
			updateGhostTouch();
		}
		break;
	case LEVEL_THREE:
		movementSpeed_GHOST = 0.35;
		updateGhostMovement(eTime, dTime);
		if (!isGhostStunned()) {
			updateGhostTouch();
		}
		break;
	case LEVEL_FOUR:
		movementSpeed_GHOST = 0.4;
		updateGhostMovement(eTime, dTime);
		if (!isGhostStunned()) {
			updateGhostTouch();
		}
		break;

	case LEVEL_FIVE: // Boss AI Logic

		movementSpeed_GHOST = 0.175; // increase movespeed of ghosts

		// Logics for all Boss phases
		switch (_AI_BOSS.phase) {

		case 1: // P1

			// Spawn 4 ghosts upon entering this stage
			if (!transitioned1 && !isKeyPressed(VK_F5) && eTime >= nextSpawnTime) {

				g_sChar.m_bStunned = true; // stop the player from moving first

				COORD ghost_pos;

				// Ghost summoning animation
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
					unstunGhosts(); // Activate all the ghosts once summoned
					g_sChar.m_bStunned = false; // Resume player movement after animation
					transitioned1 = true;
					break;

				}

			}

			// Animation done, start moving the ghost
			if (transitioned1) {
				updateGhostMovement(eTime, dTime);
				// Reset everything if player touched the ghost
				if (updateGhostTouch()) {
					transitioned1 = false;
					ghostIndex = 0;
					nextSpawnTime = eTime;
				}
			}

			// Transition to phase 2 when enough stars are collected
			if (_POINTS_ASTERISK <= 0) {
				if (_COLLECTION_OBJ_SHIELD_COUNT > 0) {
					replaceMapCharacterOnce(I_SHIELD, ' ');
					_COLLECTION_OBJ_SHIELD_COUNT--;

					if (_COLLECTION_OBJ_SHIELD_COUNT <= 0) {
						destroyGhosts();
						replaceMapCharacterAll('7', ' ');
						replaceMapCharacterAll(I_STAR, ' ');
						_AI_BOSS.phase = 2; // Shields removed, proceed to phase 2
					}
				}
			}

			break;

		case 2: // P2

			// Attempts to move boss to this location every frame
			moveBossTo(bossP2locationToMove, eTime, dTime);

			// Unstun the boss when duration is over
			if (eTime >= bossP2nextMoveTime && _AI_BOSS.stunned) {
				unstunBoss();
			}

			// Move boss to a new position now and then
			if (eTime >= bossP2nextMoveTime && !_AI_BOSS.stunned) {

				bossP2locationToMove = getRandomMapLocation();
				bossP2nextMoveTime = eTime + bossP2MoveInterval;
				bossP2movesBeforeStunned--; // Decrement each time he moves

				if (bossP2movesBeforeStunned <= 0) {
					stunBoss();
					bossP2movesBeforeStunned = bossP2StunInterval;
					bossP2nextMoveTime = eTime + bossP2StunDuration;
				}
			}

			// Shoot bullets per interval
			if (eTime >= bossP2nextShootTime && !_AI_BOSS.stunned) {

				// Spawn bullets at random direction
				spawnBullet(_AI_BOSS.pos, (E_DIRECTION_BULLET)(rand() % 7 + 1), false);
				spawnBullet(_AI_BOSS.pos, (E_DIRECTION_BULLET)(rand() % 7 + 1), false);
				spawnBullet(_AI_BOSS.pos, (E_DIRECTION_BULLET)(rand() % 7 + 1), false);
				spawnBullet(_AI_BOSS.pos, (E_DIRECTION_BULLET)(rand() % 7 + 1), false);

				bossP2nextShootTime = eTime + bossP2ShootInterval;

			}

			break;

		// Boss dying phase
		case 4:

			// Move boss to the middle
			bossP4location = { g_Map[0].size() / 2, g_Map.size() / 2 };
			moveBossTo(bossP4location, eTime, dTime);

			if (g_sChar.m_cLocation.X == _AI_BOSS.pos.X && g_sChar.m_cLocation.Y == _AI_BOSS.pos.Y) {
				// Player defeated the game!!
				closeMap();
				current_level = LEVEL_WON;
				// Reset the Phase
				_AI_BOSS.phase = 1;
			}

			break;

		case 3: // P3

			bossP3location2 = COORD{ 1, g_Map.size() - header_offset - footer_offset };
			bossP3location3 = COORD{ g_Map[0].size() / 2, g_Map.size() / 2 };

			// Character on the Right side and Top of Boss
			char b_char_Left = g_Map[_AI_BOSS.pos.Y][_AI_BOSS.pos.X - 1];
			char b_char_Right = g_Map[_AI_BOSS.pos.Y][_AI_BOSS.pos.X + 1];
			char b_char_Top = g_Map[_AI_BOSS.pos.Y - 1][_AI_BOSS.pos.X];

			// Move boss to the intial location
			if ((_AI_BOSS.pos.X != bossP3location1.X || _AI_BOSS.pos.Y != bossP3location1.Y) && bossP3Stage == 0) {
				g_sChar.m_bStunned = true; // Stun the player before transitioning
				moveBossTo(bossP3location1, eTime, dTime); // Move slowly to the initial start point
				if (_AI_BOSS.pos.X == bossP3location1.X && _AI_BOSS.pos.Y == bossP3location1.Y) { // Check if we have arrived at the start point
					bossP3Stage++; // Go to next sub-stage
					g_sChar.m_bStunned = false; // Unstun the player
				}
			}

			switch (bossP3Stage) {

			case 1:

				// Shoot bullets every set intervals
				if (eTime >= bossP3nextShootTime && !_AI_BOSS.stunned && b_char_Right != '8') {
					spawnBullet(_AI_BOSS.pos, E_DIRECTION_BULLET::LEFT, false);
					spawnBullet(_AI_BOSS.pos, E_DIRECTION_BULLET::DOWN, false);
					spawnBullet(_AI_BOSS.pos, E_DIRECTION_BULLET::RIGHT, false);
					spawnBullet(_AI_BOSS.pos, E_DIRECTION_BULLET::BOTTOMLEFT, false);
					bossP3nextShootTime = eTime + bossP3ShootInterval;
				}
				else if (b_char_Right == '8' && !_AI_BOSS.stunned) {
					stunBoss(); // Allow the player to shoot the boss for a period
					bossP3nextMoveTime = eTime + bossP3StunDuration; // Stun the boss after barraging
				}

				// Move the boss to the right
				if (eTime >= bossP3nextMoveTime && b_char_Right != '8') {
					_AI_BOSS.pos.X++;
					bossP3nextMoveTime = eTime + bossP3MoveInterval;
				}

				if (eTime >= bossP3nextMoveTime && _AI_BOSS.stunned) { // Unstun after stun duration is over
					unstunBoss();
					bossP3Stage++; // Time to transition to next sub-stage
				}

				break;
			case 2:

				// Move boss to the next location
				if (_AI_BOSS.pos.X != bossP3location2.X || _AI_BOSS.pos.Y != bossP3location2.Y) {

					moveBossTo(bossP3location2, eTime, dTime); // Move slowly to the initial start point

					if (_AI_BOSS.pos.X == bossP3location2.X && _AI_BOSS.pos.Y == bossP3location2.Y) { // Check if we have arrived at the start point
						bossP3Stage++; // Go to next sub-stage
					}
				}

				break;
			case 3:

				// Shoot bullets every set intervals
				if (eTime >= bossP3nextShootTime && !_AI_BOSS.stunned && b_char_Top != '8') {
					spawnBullet(_AI_BOSS.pos, E_DIRECTION_BULLET::DOWN, false);
					spawnBullet(_AI_BOSS.pos, E_DIRECTION_BULLET::TOPRIGHT, false);
					spawnBullet(_AI_BOSS.pos, E_DIRECTION_BULLET::RIGHT, false);
					spawnBullet(_AI_BOSS.pos, E_DIRECTION_BULLET::BOTTOMRIGHT, false);
					bossP3nextShootTime = eTime + bossP3ShootInterval;
				}
				else if (b_char_Top == '8' && !_AI_BOSS.stunned) {
					stunBoss(); // Allow the player to shoot the boss for a period
					bossP3nextMoveTime = eTime + bossP3StunDuration; // Stun the boss after barraging
				}

				// Move the boss to the top
				if (eTime >= bossP3nextMoveTime && b_char_Top != '8') {
					_AI_BOSS.pos.Y--;
					bossP3nextMoveTime = eTime + bossP3MoveInterval;
				}

				if (eTime >= bossP3nextMoveTime && _AI_BOSS.stunned) { // Unstun after stun duration is over
					unstunBoss();
					bossP3Stage++; // Time to transition to next sub-stage
				}

				break;

			case 4:

				// Move boss to the next location
				if (_AI_BOSS.pos.X != bossP3location3.X || _AI_BOSS.pos.Y != bossP3location3.Y) {

					moveBossTo(bossP3location3, eTime, dTime); // Move slowly to the initial start point

					if (_AI_BOSS.pos.X == bossP3location3.X && _AI_BOSS.pos.Y == bossP3location3.Y) { // Check if we have arrived at the start point
						bossP3Stage++; // Go to next sub-stage
					}
				}

				break;

			case 5:

				// Shoot bullets every set intervals
				if (eTime >= bossP3nextShootTime) {
					spawnBullet(_AI_BOSS.pos, direction1, false);
					spawnBullet(_AI_BOSS.pos, direction2, false);
					spawnBullet(_AI_BOSS.pos, direction3, false);
					spawnBullet(_AI_BOSS.pos, direction4, false);
					bossP3nextShootTime = eTime + bossP3ShootInterval;

					if (eTime >= bossP3nextDirectionChange) {
						direction1 = (E_DIRECTION_BULLET)(direction1 + 1);
						direction2 = (E_DIRECTION_BULLET)(direction2 + 1);
						direction3 = (E_DIRECTION_BULLET)(direction3 + 1);
						direction4 = (E_DIRECTION_BULLET)(direction4 + 1);

						// Reset the direction if it goes over the range
						if (direction1 > E_DIRECTION_BULLET::TOPLEFT) {
							direction1 = E_DIRECTION_BULLET::UP;
						}

						// Reset the direction if it goes over the range
						if (direction2 > E_DIRECTION_BULLET::TOPLEFT) {
							direction2 = E_DIRECTION_BULLET::UP;
						}

						// Reset the direction if it goes over the range
						if (direction3 > E_DIRECTION_BULLET::TOPLEFT) {
							direction3 = E_DIRECTION_BULLET::UP;
						}

						// Reset the direction if it goes over the range
						if (direction4 > E_DIRECTION_BULLET::TOPLEFT) {
							direction4 = E_DIRECTION_BULLET::UP;
						}

						bossP3nextDirectionChange = eTime + bossP3DirectionChangeInterval;

					}

				}


				if (b_char_Right == '8') {
					movingLeft = true;
				}
				else if (b_char_Left == '8') {
					movingLeft = false;
				}

				// Move left & right
				if (eTime >= bossP3nextMoveTime && !movingLeft) {
					_AI_BOSS.pos.X++;
					bossP3nextMoveTime = eTime + bossP3MoveInterval;
				}
				else if (eTime >= bossP3nextMoveTime && movingLeft) {
					_AI_BOSS.pos.X--;
					bossP3nextMoveTime = eTime + bossP3MoveInterval;
				}

				if (_AI_BOSS.pos.X == 1) {
					resetBoss();
				}

				break;

			}

			break;


		}

		break;

	}

}


void moveBossTo(COORD dest, double eTime, double dTime) {

	static double nextMoveTime = eTime;
	const double bossMoveSpeed = 0.05; // move 1 char every X seconds, lower to speed boss up

	if (eTime >= nextMoveTime) {

		// Continue movement
		if (_AI_BOSS.pos.X > dest.X) {
			_AI_BOSS.pos.X--;
		}
		else if (_AI_BOSS.pos.X < dest.X) {
			_AI_BOSS.pos.X++;
		}

		if (_AI_BOSS.pos.Y > dest.Y) {
			_AI_BOSS.pos.Y--;
		}
		else if (_AI_BOSS.pos.Y < dest.Y) {
			_AI_BOSS.pos.Y++;
		}

		if (_AI_BOSS.pos.X == g_sChar.m_cLocation.X && _AI_BOSS.pos.Y == g_sChar.m_cLocation.Y && _AI_BOSS.phase != 4) {
			closeMap();
			LEVEL_restart = current_level;
			current_level = LEVEL_OVER;
			return;
		}

		nextMoveTime = eTime + bossMoveSpeed;

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

	if (_AI_BOSS.phase > 0 && current_level == LEVEL_FIVE) {

		COORD bossPos = _AI_BOSS.pos;
		WORD colorToPrint;
		char charToPrint = AI::BOSS;

		switch (_AI_BOSS.phase) {
		case 1:
			colorToPrint = color_BOSS_P1_COLOR;
			break;
		case 2:
			colorToPrint = color_BOSS_P2_COLOR;
			break;
		case 3:
			colorToPrint = color_BOSS_P3_COLOR;
			break;
		case 4:
			colorToPrint = _OBJ_PORTAL_COLOR;
			charToPrint = I_PORTAL;
			break;
		}

		// Boss Stun Color
		if (_AI_BOSS.stunned) {
			colorToPrint = color_BOSS_STUNNED;
		}

		handle->writeToBuffer(bossPos.X, bossPos.Y + header_offset, charToPrint, colorToPrint);
	}


}

void destroyGhosts() {
	_COLLECTION_AI_GHOST.clear();
}

void destroyGhost(vector<AI_GHOST>::const_iterator i) {
	_COLLECTION_AI_GHOST.erase(i);
}

void destroyAI() {
	_COLLECTION_AI_GHOST.clear();
	transitioned1 = false;
	ghostIndex = 0;
}

void resetBoss() {

	_AI_BOSS.stunned = false;

	// Phase 1
	nextSpawnTime = 0.0;
	transitioned1 = false;
	ghostIndex = 0;

	// Phase 2
	bossP2locationToMove = getRandomMapLocation();
	bossP2nextMoveTime = 0.0;
	bossP2nextShootTime = bossP2ShootInterval;
	bossP2movesBeforeStunned = bossP2StunInterval;

	// Phase 3
	bossP3nextMoveTime = bossP3MoveInterval;
	bossP3nextShootTime = bossP3ShootInterval;
	bossP3Stage = 0;
	bossP3nextDirectionChange = bossP3DirectionChangeInterval;
	movingLeft = false;

}

void spawn_ghost(COORD pos, bool active) {
	_COLLECTION_AI_GHOST.push_back(AI_GHOST{
		_COLLECTION_AI_GHOST.size(), pos, active
	});
}

void spawn_boss(COORD pos) {

	_AI_BOSS.pos = pos;
	_AI_BOSS.health = boss_HEALTH_DEFAULT;
	_AI_BOSS.phase = 1;
	_AI_BOSS.stunned = false;
	g_sChar.health = g_PlayerDefaultHealth;

}

void stunBoss() {
	_AI_BOSS.stunned = true;
}

void unstunBoss() {
	_AI_BOSS.stunned = false;
}