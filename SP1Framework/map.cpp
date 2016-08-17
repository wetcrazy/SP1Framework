#include "map.h"

static ifstream file;
static string appender[mapHeight];

void renderMap(Console *handle, MAP level, vector< vector<char> > * ptr) {

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

	int r = 0;

	while (file.good()) {

		getline(file, buffer);
		appender[r] = buffer;

		vector<char> row;

		for (size_t i = 0; i < buffer.length(); i++) {
			row.push_back(buffer[i]);
		}

		ptr->push_back(row);

		r++;

	}

	for (int i = 0; i < mapHeight; i++) {
		handle->writeToBuffer(0, i, appender[i], 0x20);
	}

}

// Closes the file stream
void closeMap(vector< vector<char> > * map) {
	map = new vector<vector<char>>; // Release and reset map
	file.close();
}

// Test if the argument is a passable ASCII character
bool isPassable(char c) {
	for each (char ch in PASSABLES) {
		if (c == ch)
			return true;
	}
	return false;
}