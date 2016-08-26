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
		strCenter = "Avoid Ghosts & Collect Stars";
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
		strCenter = "Avoid Ghosts & Collect Stars";
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
		strCenter = "Mine the Blocks & Find the Stars";
		strRight = "Stars left : " + to_string(_POINTS_ASTERISK);
		break;
	case LEVEL_FOUR:
		strCenter = "";
		break;
	case LEVEL_FIVE:

		switch (_AI_BOSS.phase){

		case 1:
			strLeft = "-Phase 1-";
			strCenter = "Collect Stars to break the barrier!";
			strRight = "Stars left : " + to_string(_POINTS_ASTERISK);
			strTopCenter = "Boss HP: Invulnerable";
			break;

		case 2:
			strLeft = "-Phase 2-";
			strCenter = "Destroy the Boss!";
			strTopCenter = "Boss HP: ";

			for (short i = 0; i < _AI_BOSS.health; i++){
				strTopCenter += "#";
			}
			break;

		case 3:
			strLeft = "-Final Phase-";


			break;
		}

		break;
	case LEVEL_SIX:
		strCenter = "";
		break;
	case LEVEL_SEVEN:
		strCenter = "";
		break;
	case LEVEL_EIGHT:
		strCenter = "";
		break;
	case LEVEL_NINE:
		strCenter = "";
		break;
	case LEVEL_TEN:
		strCenter = "";
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