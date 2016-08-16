#include "map.h"

static ifstream file;
static string appender = "";

void renderMap(Console *handle, MAP level, char ptr[][mapHeight]) {

	string buffer;

	if (!file.is_open()) {
		switch (level) {

		case LEVEL_ONE:
			file.open("level_one.txt");
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
	int row = 0;

	while (file.good()) {

		getline(file, buffer);
		appender += (buffer + "\n");

		for (int i = 0; i < buffer.length(); i++) {
			ptr[row][i] = buffer[i];
		}
		row++;
	}

	handle->writeToBuffer(0, 0, appender);
	// TODO, find out how to new line with wincon.h

}

// Closes the file stream
void closeMap() {
	appender = "";
	file.close();
}