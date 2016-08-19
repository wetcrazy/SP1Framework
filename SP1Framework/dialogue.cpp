#include "dialogue.h"
#include "score.h"



void dialogue(Console * handle)
{

	WORD dialogColor = 0x03;

	string strLeft;
	string strCenter;
	string strRight;

	switch (current_level)
	{

	case LEVEL_ONE:
		strLeft = "Level 1";
		strCenter = "Collect the '*'";
		strRight = "Asterisks left : " + to_string(_POINTS_ASTERISK);
		break;
	case LEVEL_TWO:
		strCenter = "Solve the puzzle";
		break;
	case LEVEL_THREE:
		strCenter = "";
		break;
	case LEVEL_FOUR:
		strCenter = "";
		break;
	case LEVEL_FIVE:
		strCenter = "";
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
	COORD cLeft = handle->getConsoleSize();
	cLeft.X = 0;
	cLeft.Y -= 1;
	COORD cCenter = handle->getConsoleSize();
	cCenter.X  = (cCenter.X / 2) - (strCenter.length() / 2);
	cCenter.Y -= 1;
	COORD cRight = handle->getConsoleSize();
	cRight.X -= (strRight.length());
	cRight.Y -= 1;

	// Output to console
	handle->writeToBuffer(cLeft, strLeft, dialogColor);
	handle->writeToBuffer(cCenter, strCenter, dialogColor);
	handle->writeToBuffer(cRight, strRight, dialogColor);

}