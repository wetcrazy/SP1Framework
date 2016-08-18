#include "map.h"

static ifstream file;
static MAP _Current_Map;

void renderMap(Console *handle, MAP level, vector< vector<char> > * ptr) {

	_Current_Map = level;

	string buffer;

	if (!file.is_open()) {
		switch (level) {

		case LEVEL_TITLE:
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

	// Write to pointer
	while (file.good()) {

		getline(file, buffer);

		vector<char> row;

		for (size_t i = 0; i < buffer.length() + 1; i++) {
				row.push_back(buffer[i]);
		}

		ptr->push_back(row);

		r++;

	}

	// Print out the data from the pointer vector
	for (int i = 0; i < ptr->size(); i++) {
		string s = "";
		for (int k = 0; k < ptr->at(i).size(); k++) {
			s += ptr->at(i).at(k);
		}
		handle->writeToBuffer(0, i + header_offset, s, 0x20); // offset Y by 1 for the fps
	}

}

// Closes the file stream
void closeMap(vector< vector<char> > * map) {
	map->clear(); // Release and reset map
	file.close();
}

