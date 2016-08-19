#include "map.h"
#include "_interactable.h"
#include "Framework\console.h"

static ifstream file;

MAP current_level = LEVEL_TITLE;
vector< vector<char> > g_Map;

void renderMap(Console *handle) {

	WORD color = 0xF0;

	string buffer;
	if (!file.is_open()) {
		switch (current_level) {

		case LEVEL_TITLE:
		case LEVEL_MENU:
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

	int row = 0;

	while (file.good()) {

		getline(file, buffer);

		vector<char> vecRowBuffer;

		for (size_t col = 0; col < buffer.length() + 1; col++) {
			vecRowBuffer.push_back(buffer[col]);

			// Is the character an interactable object?
			if (isInteractable(buffer[col])) {

				COORD pos = { row, col };

				switch (current_level) {

				case LEVEL_ONE:
				case LEVEL_TWO:
					_OBJ_COLLECTION_STAR.push_back(STAR{
						pos
					});
					_OBJ_COLLECTION_PORTAL.push_back(PORTAL{
						pos
					});
					break;

				}

			}

		}

		g_Map.push_back(vecRowBuffer);

		row++;

	}

	for (size_t col = 0; col < g_Map.size(); col++) {
		string s = "";
		for (size_t k = 0; k < g_Map.at(col).size(); k++) {
			if (g_Map.at(col).at(k) == '8') {
				s += 219;
			}
			else {
				s += g_Map.at(col).at(k);
			}
			
		}
		handle->writeToBuffer(0, col + header_offset, s, color);
	}

}

// Closes the file stream
void closeMap() {
	g_Map.clear(); // Release and reset map
	file.close();
}