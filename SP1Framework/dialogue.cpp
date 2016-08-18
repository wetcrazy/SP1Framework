#include "dialogue.h"



void dialogue(Console * handle)
{

	string str;

	switch (current_level)
	{

	case LEVEL_ONE:
		str = "Collect the '*'";
		break;
	case LEVEL_TWO:
		str = "Solve the puzzle";
		break;
	case LEVEL_THREE:
		str = "";
		break;
	case LEVEL_FOUR:
		str = "";
		break;
	case LEVEL_FIVE:
		str = "";
		break;
	case LEVEL_SIX:
		str = "";
		break;
	case LEVEL_SEVEN:
		str = "";
		break;
	case LEVEL_EIGHT:
		str = "";
		break;
	case LEVEL_NINE:
		str = "";
		break;
	case LEVEL_TEN:
		str = "";
		break;




	}


	COORD c = handle->getConsoleSize();
	
	c.Y --;
	c.X = (c.X / 2) - (str.length() / 2);

	handle->writeToBuffer(c, str, 0x03);

}