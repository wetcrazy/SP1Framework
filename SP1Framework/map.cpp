#include "map.h"

static ifstream file;
static string appender[mapHeight];

void renderMap(Console *handle, MAP level, char ptr[][mapHeight]) {

	string buffer;

	if (!file.is_open()) {
		switch (level) {

		case LEVEL_ONE:
		case LEVEL_TWO:
		case LEVEL_THREE:
		case LEVEL_FOUR:
		case LEVEL_FIVE:
		case LEVEL_SIX:
		case LEVEL_SEVEN:
		case LEVEL_EIGHT:
		case LEVEL_NINE:
		case LEVEL_TEN:
			file.open("level_" + to_string(level) + ".txt");
			break;

		}
	}
	int row = 0;

	while (file.good()) {

		getline(file, buffer);
		appender[row] = buffer;

		for (size_t i = 0; i < buffer.length(); i++) {
			ptr[row][i] = buffer[i];
		}
		row++;
	}

	for (int i = 0; i < mapHeight; i++) {
			handle->writeToBuffer(0, i, appender[i], 0x20);
	}

}

// Closes the file stream
void closeMap() {
	file.close();
}