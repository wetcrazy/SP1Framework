#include "skills.h"
#include "_interactable.h"


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
			COORD PlayerCord = g_sChar.m_cLocation;

			// Is the block solid or blank
			if ((g_Map[PlayerCord.Y - 1][PlayerCord.X] == '8'))// UP
			{
				g_Map[PlayerCord.Y - 1][PlayerCord.X] = ' ';
			}
			else if ((g_Map[PlayerCord.Y + 1][PlayerCord.X] == '8'))// DOWN
			{
				g_Map[PlayerCord.Y + 1][PlayerCord.X] = ' ';
			}
			else if ((g_Map[PlayerCord.Y][PlayerCord.X - 1] == '8'))// RIGHT
			{
				g_Map[PlayerCord.Y][PlayerCord.X - 1] = ' ';
			}
			else if ((g_Map[PlayerCord.Y][PlayerCord.X + 1] == '8'))// LEFT
			{
				g_Map[PlayerCord.Y][PlayerCord.X + 1] = ' ';
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