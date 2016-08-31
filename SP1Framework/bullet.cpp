#include "bullet.h"



vector<BULLET> _OBJ_COLLECTION_BULLET;

// Bullet moves 1 character every X seconds, lower to speed it up
const double bulletSpeed = 0.01;


void spawnBullet(COORD pos, E_DIRECTION_BULLET direction, bool isPlayer) {

	_OBJ_COLLECTION_BULLET.push_back({
		pos, direction, isPlayer
	});

}


void updateBullets(double eTime, double dTime) {

	static double nextMoveTime = eTime;

	if (eTime >= nextMoveTime) {

		for (auto i = _OBJ_COLLECTION_BULLET.begin(); i != _OBJ_COLLECTION_BULLET.end(); ++i) {

			switch (i->direction) {

			case E_DIRECTION_BULLET::UP:
				i->pos.Y -= 1;
				break;

			case E_DIRECTION_BULLET::DOWN:
				i->pos.Y += 1;
				break;

			case E_DIRECTION_BULLET::LEFT:
				i->pos.X -= 1;
				break;

			case E_DIRECTION_BULLET::RIGHT:
				i->pos.X += 1;
				break;

			case E_DIRECTION_BULLET::TOPLEFT:
				i->pos.X -=  1;
				i->pos.Y -= 1;
				break;

			case E_DIRECTION_BULLET::TOPRIGHT:
				i->pos.X += 1;
				i->pos.Y -= 1;
				break;

			case E_DIRECTION_BULLET::BOTTOMLEFT:
				i->pos.X -= 1;
				i->pos.Y += 1;
				break;

			case E_DIRECTION_BULLET::BOTTOMRIGHT:
				i->pos.X += 1;
				i->pos.Y += 1;
				break;

			}

			if (i->isPlayer) { // bullet from player

				if (i->pos.X == _AI_BOSS.pos.X && i->pos.Y == _AI_BOSS.pos.Y) { // Check if bullet hit the boss
					_AI_BOSS.health--;

					// Boss died, go phase 3!
					if (_AI_BOSS.health <= 0 && _AI_BOSS.phase == 2) {
						_AI_BOSS.stunned = false;
						_AI_BOSS.phase = 3;
						_AI_BOSS.health = boss_HEALTH_DEFAULT_P3;
					}

					// Player defeated phase 3
					if (_AI_BOSS.health <= 0 && _AI_BOSS.phase == 3) {
						resetBoss();
						_AI_BOSS.phase = 4;
					}


				}

			}
			else { // bullet from boss

				if (i->pos.X == g_sChar.m_cLocation.X && i->pos.Y == g_sChar.m_cLocation.Y) {
					g_sChar.health--;

					// Player died, do necessary clean up here
					if (g_sChar.health <= 0) {
						closeMap();
						_OBJ_COLLECTION_BULLET.clear();
						resetBoss();
						LEVEL_restart = current_level;
						current_level = LEVEL_OVER;
						return;
					}
				}

			}

			// Player's bullet hit the boss
			if (i->isPlayer && i->pos.X == _AI_BOSS.pos.X && i->pos.Y == _AI_BOSS.pos.Y) {
				destroyBullet(i);
				break;
			}

			// Boss's bullet hit the player
			if (!i->isPlayer && i->pos.X == g_sChar.m_cLocation.X && i->pos.Y == g_sChar.m_cLocation.Y) {
				destroyBullet(i);
				break;
			}

			// Removes bullet on collision with something else
			if (g_Map[i->pos.Y][i->pos.X] != ' ') {
				destroyBullet(i);
				break;
			}

		}

		nextMoveTime = eTime + bulletSpeed;

	}

}

void renderBullets(Console * handle, double eTime, double dTime) {

	COORD pos;

	for (size_t i = 0; i < _OBJ_COLLECTION_BULLET.size(); i++) {

		char charToPrint = I_STAR;
		WORD colorToPrint = bulletPlayerColor;

		BULLET * bullet = &_OBJ_COLLECTION_BULLET[i];
		pos = _OBJ_COLLECTION_BULLET[i].pos;

		// Bullets Position Offset
		switch (bullet->direction) {

		case E_DIRECTION_BULLET::LEFT:
			pos.Y += header_offset;
			pos.X -= header_offset;
			break;
		case E_DIRECTION_BULLET::RIGHT:
			pos.Y += header_offset;
			pos.X += header_offset;
			break;

		case E_DIRECTION_BULLET::DOWN:
			pos.Y += (header_offset * 2);
			break;

		case E_DIRECTION_BULLET::BOTTOMLEFT:
			pos.Y += header_offset;
			break;

		}

		// Change bullet's color if it is owned by boss
		if (!bullet->isPlayer) {
			charToPrint = I_ENEMY_STAR;
			colorToPrint = bulletBossColor;
		}

		handle->writeToBuffer(pos, charToPrint, colorToPrint);
	}

}

void destroyBullet(vector<BULLET>::const_iterator index) {

	_OBJ_COLLECTION_BULLET.erase(index);

}

void destroyAllBullet()
{
	_OBJ_COLLECTION_BULLET.clear();
}