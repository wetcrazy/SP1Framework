#include "skills.h"
#include "_interactable.h"
#include "bullet.h"


short SKILL_STUN_CHARGES = 3;
short SKILL_MINING = 2;


// Use the skills available and appropriate to the current_level
void processSkill(Console * handle, double dTime) {

	static bool canPress = true;

	switch (current_level) {

	case LEVEL_ONE:
	case LEVEL_TWO:

		// KeyUp = true
		if (!isKeyPressed(VK_SPACE)) {
			canPress = true;
		}

		if (isKeyPressed(VK_SPACE) && canPress) {

			// Stun ghosts if we still have charges
			if (SKILL_STUN_CHARGES > 0) {
				stunGhosts();
				SKILL_STUN_CHARGES--;
				canPress = false;
			}

		}
		break;
	case LEVEL_THREE:
		if (isKeyPressed(VK_SPACE)) {
			COORD PlayerCord = g_sChar.m_cLocation;// PLAYER COORDINATES
			size_t rng = rand() % 50;
			static size_t Num_Stars = 0;
			static size_t Max_Stars = 10;
			static COORD Position;

			// If the block solid or blank, destroy~~

			if ((isKeyPressed(VK_UP)) && (g_Map[PlayerCord.Y - 1][PlayerCord.X] == '7'))// UP
			{
				if (Num_Stars < Max_Stars) {
					if (rng == 6) {

						g_Map[PlayerCord.Y - 1][PlayerCord.X] = '*';
						Position = { PlayerCord.Y - 1, PlayerCord.X };
						Num_Stars++;
						_COLLECTION_OBJ_STAR.push_back(STAR{ Position });
					}
					else {
						g_Map[PlayerCord.Y - 1][PlayerCord.X] = ' ';
					}
				}
				else {
					g_Map[PlayerCord.Y - 1][PlayerCord.X] = ' ';
				}
			}
			else if ((isKeyPressed(VK_DOWN)) && (g_Map[PlayerCord.Y + 1][PlayerCord.X] == '7'))// DOWN
			{
				if (Num_Stars < Max_Stars) {
					if (rng == 6) {
						g_Map[PlayerCord.Y + 1][PlayerCord.X] = '*';
						Position = { PlayerCord.Y + 1, PlayerCord.X };
						Num_Stars++;
						_COLLECTION_OBJ_STAR.push_back(STAR{ Position });
					}
					else {
						g_Map[PlayerCord.Y + 1][PlayerCord.X] = ' ';
					}
				}
				else {
					g_Map[PlayerCord.Y + 1][PlayerCord.X] = ' ';
				}
			}
			else if ((isKeyPressed(VK_LEFT)) && (g_Map[PlayerCord.Y][PlayerCord.X - 1] == '7'))// LEFT
			{
				if (Num_Stars < Max_Stars) {
					if (rng == 6) {
						g_Map[PlayerCord.Y][PlayerCord.X - 1] = '*';
						Position = { PlayerCord.Y, PlayerCord.X - 1 };
						Num_Stars++;
						_COLLECTION_OBJ_STAR.push_back(STAR{ Position });
					}
					else {
						g_Map[PlayerCord.Y][PlayerCord.X - 1] = ' ';
					}
				}
				else {
					g_Map[PlayerCord.Y][PlayerCord.X - 1] = ' ';
				}
			}
			else if ((isKeyPressed(VK_RIGHT)) && (g_Map[PlayerCord.Y][PlayerCord.X + 1] == '7'))// RIGHT
			{
				if (Num_Stars < Max_Stars) {
					if (rng == 6) {
						g_Map[PlayerCord.Y][PlayerCord.X + 1] = '*';
						Position = { PlayerCord.Y, PlayerCord.X + 1 };
						Num_Stars++;
						_COLLECTION_OBJ_STAR.push_back(STAR{ Position });
					}
					else {
						g_Map[PlayerCord.Y][PlayerCord.X + 1] = ' ';
					}
				}
				else {
					g_Map[PlayerCord.Y][PlayerCord.X + 1] = ' ';
				}
			}

		}
		break;

		// Player shooting in Boss Level
	case LEVEL_FIVE:

		updateBullets(g_dElapsedTime, dTime);

		static double nextFiringTime = g_dElapsedTime;
		const double firingSpeed = 0.2; // reduce this to make the player shoot faster

		if (isKeyPressed(VK_SPACE) && _AI_BOSS.phase > 1 && g_dElapsedTime >= nextFiringTime) {

			nextFiringTime = g_dElapsedTime + firingSpeed;

			COORD Player_Cord = g_sChar.m_cLocation;

			switch (g_sChar.direction) {

			case D_UP:
				spawnBullet(g_sChar.m_cLocation, E_DIRECTION_BULLET::UP, true);
				break;
			case D_DOWN:
				spawnBullet(g_sChar.m_cLocation, E_DIRECTION_BULLET::DOWN, true);
				break;
			case D_LEFT:
				spawnBullet(g_sChar.m_cLocation, E_DIRECTION_BULLET::LEFT, true);
				break;
			case D_RIGHT:
				spawnBullet(g_sChar.m_cLocation, E_DIRECTION_BULLET::RIGHT, true);
				break;
			case D_TOPLEFT:
				spawnBullet(g_sChar.m_cLocation, E_DIRECTION_BULLET::TOPLEFT, true);
				break;
			case D_TOPRIGHT:
				spawnBullet(g_sChar.m_cLocation, E_DIRECTION_BULLET::TOPRIGHT, true);
				break;
			case D_BOTTOMLEFT:
				spawnBullet(g_sChar.m_cLocation, E_DIRECTION_BULLET::BOTTOMLEFT, true);
				break;
			case D_BOTTOMRIGHT:
				spawnBullet(g_sChar.m_cLocation, E_DIRECTION_BULLET::BOTTOMRIGHT, true);
				break;

			}
		}

		break;
	}
}

short getSkillStunCharges() {
	return SKILL_STUN_CHARGES;
}

void resetSkillStunCharges() {
	SKILL_STUN_CHARGES = 3;
}