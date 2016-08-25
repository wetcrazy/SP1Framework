#include "skills.h"



short SKILL_STUN_CHARGES = 3;
short SKILL_MINING = 2;


// Use the skills available and appropriate to the current_level
void processSkill(double dTime) {

	static bool canPress = true;
	static bool PressCan = true;

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
	case LEVEL_FOUR:
		if (isKeyPressed(VK_SPACE))
		{
			COORD PlayerCord = g_sChar.m_cLocation;// PLAYER COORDINATES
			size_t rng = rand() % 10;
			static size_t Num_Stars = 0;
			static size_t Max_Stars = 10;

			// If the block solid or blank, destroy~~
			if ((isKeyPressed(VK_UP)) && (g_Map[PlayerCord.Y - 1][PlayerCord.X] == '8'))// UP
			{
				if (Num_Stars < Max_Stars)
				{
					if (rng == 6)
					{
						g_Map[PlayerCord.Y - 1][PlayerCord.X] = '*';
						Num_Stars++;
					}
					else
					{
						g_Map[PlayerCord.Y - 1][PlayerCord.X] = ' ';
					}					
				}
				else
				{
					g_Map[PlayerCord.Y - 1][PlayerCord.X] = ' ';
				}
			}
			else if ((isKeyPressed(VK_DOWN)) && (g_Map[PlayerCord.Y + 1][PlayerCord.X] == '8'))// DOWN
			{
				if (Num_Stars < Max_Stars)
				{
					if (rng == 6)
					{
						g_Map[PlayerCord.Y + 1][PlayerCord.X] = '*';
						Num_Stars++;
					}
					else
					{
						g_Map[PlayerCord.Y + 1][PlayerCord.X] = ' ';
					}
				}
				else
				{
					g_Map[PlayerCord.Y + 1][PlayerCord.X] = ' ';
				}
			}
			else if ((isKeyPressed(VK_LEFT)) && (g_Map[PlayerCord.Y][PlayerCord.X - 1] == '8'))// LEFT
			{
				if (Num_Stars < Max_Stars)
				{
					if (rng == 6)
					{
						g_Map[PlayerCord.Y][PlayerCord.X - 1] = '*';
						Num_Stars++;
					}
					else
					{
						g_Map[PlayerCord.Y][PlayerCord.X - 1] = ' ';
					}
				}
				else
				{
					g_Map[PlayerCord.Y][PlayerCord.X - 1] = ' ';
				}
			}
			else if ((isKeyPressed(VK_RIGHT)) && (g_Map[PlayerCord.Y][PlayerCord.X + 1] == '8'))// RIGHT
			{
				if (Num_Stars < Max_Stars)
				{
					if (rng == 6)
					{
						g_Map[PlayerCord.Y][PlayerCord.X + 1] = '*';
						Num_Stars++;
					}
					else
					{
						g_Map[PlayerCord.Y][PlayerCord.X + 1] = ' ';
					}
				}
				else
				{
					g_Map[PlayerCord.Y][PlayerCord.X + 1] = ' ';
				}				
			}

		}
		break;
	}
}


//void ProcessSkillBoss(double dtime)
//{
//	static bool CanPressBoss = true;
//	
//	while (LEVEL_TEN)
//	{
//		if (!isKeyPressed(VK_SPACE))
//		{
//			CanPressBoss = true;
//		}
//
//		if (isKeyPressed(VK_SPACE) && CanPressBoss)
//		{
//			
//		}
//	}
//}

short getSkillStunCharges() {
	return SKILL_STUN_CHARGES;
}

void resetSkillStunCharges() {
	SKILL_STUN_CHARGES = 3;
}