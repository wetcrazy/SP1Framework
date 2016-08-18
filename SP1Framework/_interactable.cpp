#include "_interactable.h"





// Test if the argument is a passable ASCII character
bool isPassable(char c) {
	for each (char ch in PASSABLES) {
		if (c == ch)
			return true;
	}
	return false;
}

void renderObjects(MAP map) {

	switch (map) {
	case LEVEL_TITLE:
		break;
	case LEVEL_MENU:
		break;
	case LEVEL_ONE:
		
		break;
	case LEVEL_TWO:
		break;
	case LEVEL_THREE:
		break;
	case LEVEL_FOUR:
		break;
	case LEVEL_FIVE:
		break;
	case LEVEL_SIX:
		break;
	case LEVEL_SEVEN:
		break;
	case LEVEL_EIGHT:
		break;
	case LEVEL_NINE:
		break;
	case LEVEL_TEN:
		break;
	}


}