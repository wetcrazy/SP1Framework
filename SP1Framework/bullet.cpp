#include "bullet.h"



vector<BULLET> _OBJ_COLLECTION_BULLET;

// Bullet moves 1 character every X seconds, lower to speed it up
const double bulletSpeed = 0.01;

void spawnBullet(COORD pos, E_DIRECTION_BULLET direction, bool isPlayer) {

	_OBJ_COLLECTION_BULLET.push_back({
		_OBJ_COLLECTION_BULLET.size(), pos, direction, isPlayer
	});

}


void updateBullets(double eTime, double dTime) {

	static double nextMoveTime = eTime;

	if (eTime >= nextMoveTime) {

		for (size_t i = 0; i < _OBJ_COLLECTION_BULLET.size(); i++) {

			BULLET *b = &_OBJ_COLLECTION_BULLET[i];
			switch (b->direction) {

			case E_DIRECTION_BULLET::UP:
				b->pos.Y -= 1;
				break;

			case E_DIRECTION_BULLET::DOWN:
				b->pos.Y += 1;
				break;

			case E_DIRECTION_BULLET::LEFT:
				b->pos.X -= 1;
				break;

			case E_DIRECTION_BULLET::RIGHT:
				b->pos.X += 1;
				break;

			case E_DIRECTION_BULLET::TOPLEFT:

				break;

			case E_DIRECTION_BULLET::TOPRIGHT:

				break;

			case E_DIRECTION_BULLET::BOTTOMLEFT:

				break;

			case E_DIRECTION_BULLET::BOTTOMRIGHT:

				break;

			}

			// TODO: process collision logic
			if (b->isPlayer) {

			}
			else {

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

		}

		// Change bullet's color if it is owned by boss
		if (!bullet->isPlayer) {
			charToPrint = I_ENEMY_STAR;
			colorToPrint = bulletBossColor;
		}

		handle->writeToBuffer(pos, charToPrint, colorToPrint);
	}

}

void destroyBullet(int index) {

	for (size_t i = 0; i < _OBJ_COLLECTION_BULLET.size(); i++) {
		if (_OBJ_COLLECTION_BULLET[i].index == index) {
			_OBJ_COLLECTION_BULLET.erase(_OBJ_COLLECTION_BULLET.begin() + index); // remove this element
		}
	}

}