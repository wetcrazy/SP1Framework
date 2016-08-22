#include "skills.h"



short SKILL_STUN_CHARGES = 3;



// Use the skills available and appropriate to the current_level
void processSkill(double dTime) {

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


	}


}

short getSkillStunCharges() {
	return SKILL_STUN_CHARGES;
}