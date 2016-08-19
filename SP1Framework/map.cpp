#include "map.h"
#include "_interactable.h"
#include "Framework\console.h"

static ifstream file;

MAP current_level = LEVEL_TITLE;
vector< vector<char> > g_Map;

void renderMap(Console *handle) {

	string buffer;
	if (!file.is_open()) {
		switch (current_level) {

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
			file.open("level_" + to_string(current_level) + ".txt");
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

		g_Map.push_back(row);

		r++;

	}

	for (size_t i = 0; i < g_Map.size(); i++) {
		string s = "";
		for (size_t k = 0; k < g_Map.at(i).size(); k++) {
			s += g_Map.at(i).at(k);
		}
		handle->writeToBuffer(0, i + header_offset, s, 0x20);
	}

}

// Closes the file stream
void closeMap() {
	g_Map.clear(); // Release and reset map
	file.close();
}