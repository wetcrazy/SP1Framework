#include "map.h"
#include "_interactable.h"
#include "Framework\console.h"

static ifstream file;

MAP current_level = LEVEL_TITLE;
vector< vector<char> > g_Map;
WORD mapColor = 0xF0;
unsigned char mapWalls = 0xDB;

void renderMap(Console *handle) {



	string buffer; // Buffer that contains the line of string that we read from the text file

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

	// Did map changed?
	while (file.good()) {

		getline(file, buffer);

		vector<char> vecRowBuffer;

		for (size_t col = 0; col < buffer.length() + 1; col++) {
			vecRowBuffer.push_back(buffer[col]);

			// Is the character an interactable object?
			if (isInteractable(buffer[col])) {

				COORD pos = { col, row };

				switch (current_level) {

				case LEVEL_ONE:
				case LEVEL_TWO:

					if (buffer[col] == I_STAR) {
						_OBJ_COLLECTION_STAR.push_back(STAR{
							pos
						});
					}
					if (buffer[col] == I_PORTAL) {
						_OBJ_COLLECTION_PORTAL.push_back(PORTAL{
							_OBJ_COLLECTION_PORTAL.size(), pos, true
						});
					}

					break;

				}

			}

		}

		g_Map.push_back(vecRowBuffer);
		row++;

	}

	// Output everything in g_Map to Console
	for (size_t row = 0; row < g_Map.size(); row++) {
		string s = "";
		for (size_t col = 0; col < g_Map.at(row).size(); col++) {
			if (g_Map.at(row).at(col) == '8') {
				s += mapWalls;
			}
			else {
				s += g_Map.at(row).at(col);
			}

		}
		handle->writeToBuffer(0, row + header_offset, s, mapColor);
	}

}

// Closes the file stream
void closeMap() {
	g_Map.clear(); // Release and reset map
	file.close();
}