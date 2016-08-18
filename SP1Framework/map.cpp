#include "map.h"
#include "_interactable.h"
#include "Framework\console.h"

static ifstream file;

MAP current_level;
vector< vector<char> > g_Map;

void renderMap(Console *handle, MAP level, vector< vector<char> > * ptr) {

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
			current_level = level;
			break;

		}
	}

	int r = 0;

	while (file.good()) {

		getline(file, buffer);

		vector<char> row;

		for (size_t i = 0; i < buffer.length() + 1; i++) {
			row.push_back(buffer[i]);

			// Is the character an interactable object?
			if (isInteractable(buffer[i])) {

				COORD pos = { r, i };

				switch (current_level) {

				case LEVEL_ONE:
					_OBJ_COLLECTION_STAR.push_back(STAR{
						pos
					});
					break;

				}

			}

		}

		ptr->push_back(row);

		r++;

	}

	for (size_t i = 0; i < ptr->size(); i++) {
		string s = "";
		for (size_t k = 0; k < ptr->at(i).size(); k++) {
			s += ptr->at(i).at(k);
		}
		handle->writeToBuffer(0, i + header_offset, s, 0x20);
	}

}

// Closes the file stream
void closeMap(vector< vector<char> > * map) {
	map->clear(); // Release and reset map
	file.close();
}