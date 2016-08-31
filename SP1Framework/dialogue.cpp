#include "dialogue.h"
#include "score.h"
#include "skills.h"



void dialogue(Console * handle) {

	WORD dialogColor = 0x1F;

	string strTopCenter;
	string strLeft;
	string strCenter;
	string strRight;

	switch (current_level) {

	case LEVEL_ONE:
		strLeft = "Stage 1";
		strCenter = (_POINTS_ASTERISK > 0) ? "Avoid Ghosts & Collect Stars" :  "The Gate has been Unlocked";
		strRight = "Stars left : " + to_string(_POINTS_ASTERISK);
		strTopCenter = "Flash:";
		if (getSkillStunCharges() == 0) {
			strTopCenter += " Empty";
		}
		else {
			for (short i = 0; i < getSkillStunCharges(); i++) {
				strTopCenter += "#";
			}
		}

		break;

	case LEVEL_TWO:
		strLeft = "Stage 2";
		strCenter = (_POINTS_ASTERISK > 0) ? "Avoid Ghosts & Collect Stars" : "The Gate has been Unlocked";
		strRight = "Stars left : " + to_string(_POINTS_ASTERISK);
		strTopCenter = "Flash:";
		if (getSkillStunCharges() == 0) {
			strTopCenter += " Empty";
		}
		else {
			for (short i = 0; i < getSkillStunCharges(); i++) {
				strTopCenter += "#";
			}
		}
		break;
	case LEVEL_THREE:
		strLeft = "Stage 3";
		strCenter = (_POINTS_ASTERISK > 0) ? "Mine the Blocks & Find the Stars" : "A mysterious portal has been spawned";
		strRight = "Stars left : " + to_string(_POINTS_ASTERISK);
		if (_POINTS_ASTERISK < 0) {
			strRight = "Stars left : 0";
		}
		break;
	case LEVEL_FOUR:
		strLeft = "Stage 4";
		strCenter = (_POINTS_ASTERISK > 0) ? "Mine the Blocks & Find the Stars" : "The same mysterious portal spawned again";
		strRight = "Stars left : " + to_string(_POINTS_ASTERISK);
		if (_POINTS_ASTERISK < 0) {
			strRight = "Stars left : 0";
		}
		break;
	case LEVEL_FIVE:

		switch (_AI_BOSS.phase) {

		case 1:
			strLeft = "-Phase 1-";
			strCenter = "Collect the Stars to break the barrier!";
			strRight = "Stars left : " + to_string(_POINTS_ASTERISK);
			strTopCenter = "Boss HP: Invulnerable";
			break;

		case 2:
			strLeft = "-Phase 2-";
			strCenter = "Weaken the Boss!";
			strRight = "My HP: ";
			strTopCenter = "Boss HP: ";

			for (short i = 0; i < _AI_BOSS.health; i++) {
				strTopCenter += "#";
			}
			for (short i = 0; i < g_sChar.health; i++) {
				strRight += "#";
			}
			break;

		case 3:
			strLeft = "-Final Phase-";
			strCenter = "Finish the Boss!";
			strRight = "My HP: ";
			strTopCenter = "Boss HP: ";

			for (short i = 0; i < _AI_BOSS.health; i++) {
				strTopCenter += "#";
			}
			for (short i = 0; i < g_sChar.health; i++) {
				strRight += "#";
			}
			break;

		case 4:
			strCenter = "A portal appears in the middle";
			break;

		}

		break;

	}


	// Alignment for the strings
	COORD cTopCenter = handle->getConsoleSize();
	cTopCenter.X = (cTopCenter.X / 2) - (strTopCenter.length() / 2);
	cTopCenter.Y = 0;
	COORD cLeft = handle->getConsoleSize();
	cLeft.X = 0;
	cLeft.Y -= 1;
	COORD cCenter = handle->getConsoleSize();
	cCenter.X = (cCenter.X / 2) - (strCenter.length() / 2);
	cCenter.Y -= 1;
	COORD cRight = handle->getConsoleSize();
	cRight.X -= (strRight.length());
	cRight.Y -= 1;

	// Output to console
	handle->writeToBuffer(cTopCenter, strTopCenter);
	handle->writeToBuffer(cLeft, strLeft);
	handle->writeToBuffer(cCenter, strCenter);
	handle->writeToBuffer(cRight, strRight);

}