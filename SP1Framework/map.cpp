#include "map.h"
#include "_interactable.h"
#include "Framework\console.h"
#include "_AI.h"
#include "skills.h"
#include "score.h"

static ifstream file;

MAP LEVEL_restart;
MAP current_level;

vector< vector<char> > g_Map;

const short fogWidth = 8;
const short fogHeight = 4;

const WORD mapColor = 0xF8;
const WORD fogColor = 0x0F;

const unsigned char mapWalls = 0xDB;

void renderMap(Console *handle) {



	string buffer; // Buffer that contains the line of string that we read from the text file

	// Load map if it is not currently loaded
	if (!file.is_open()) {
		switch (current_level) {
		case LEVEL_OVER:
			file.open("level_" + to_string(current_level) + ".txt");
			g_eGameState = S_GAMEOVER;
			break;
		case LEVEL_TITLE:
			file.open("level_" + to_string(current_level) + ".txt");
			g_eGameState = S_TITLESCREEN;
			break;
		case LEVEL_MENU:
			file.open("level_" + to_string(current_level) + ".txt");
			g_eGameState = S_MENU;
			break;
		case LEVEL_ONE:
		case LEVEL_TWO:
			g_sChar.m_cLocation = handle->getConsoleSize(); // Spawn player at middle
			g_sChar.m_cLocation.X /= 2;
			g_sChar.m_cLocation.Y /= 2;
		case LEVEL_THREE:
		case LEVEL_FOUR:
		case LEVEL_FIVE:
		case LEVEL_SIX:
		case LEVEL_SEVEN:
		case LEVEL_EIGHT:
		case LEVEL_NINE:
		case LEVEL_TEN:
			g_eGameState = S_GAME;
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

			// Is the character an interactable object?
			if (isInteractable(buffer[col]) || isNPC(buffer[col])) {

				COORD pos = { col, row };

				// Store the objects to the vector collection
				switch (current_level) {

				case LEVEL_ONE:
				case LEVEL_TWO:

					if (buffer[col] == I_STAR) {
						_COLLECTION_OBJ_STAR.push_back(STAR{
							pos
						});
					}

					if (buffer[col] == I_PORTAL) {
						_COLLECTION_OBJ_PORTAL.push_back(PORTAL{
							_COLLECTION_OBJ_PORTAL.size(), pos, true
						});
					}

					if (buffer[col] == I_EXIT_INACTIVE) {
						_COLLECTION_OBJ_EXIT.push_back(EXIT{
							pos, false
						});
					}

					if (buffer[col] == AI::GHOST) {

						buffer[col] = ' '; // Remove the ghost and let AI.cpp manually control it

						_COLLECTION_AI_GHOST.push_back(AI_GHOST{
							_COLLECTION_AI_GHOST.size(), pos, true
						});
					}

					break;

				}

			}

			vecRowBuffer.push_back(buffer[col]);

		}

		g_Map.push_back(vecRowBuffer);
		row++;

	}

	// Output everything in g_Map to Console
	for (size_t row = 0; row < g_Map.size(); row++) {
		string s = "";
		for (size_t col = 0; col < g_Map.at(row).size(); col++) {
			// Change '8' to a mazey character
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

void renderFog(Console * handle) {

	string str = " ";

	for (short row = 0; row < g_Map.size(); row++) {

		for (short col = 0; col < g_Map[row].size(); col++) {

			COORD playerPos = g_sChar.m_cLocation;

			// Skip printing of fog if it falls within the player's vision radius
			if (playerPos.X >= (col - fogWidth) && playerPos.X <= (col + fogWidth) && playerPos.Y <= (row + fogHeight) && playerPos.Y >= (row - fogHeight)) {
				continue;
			}

			// Dont apply fog to the exit
			if (g_Map[row][col] == I_EXIT_INACTIVE || g_Map[row][col] == I_EXIT_ACTIVE) {
				continue;
			}

			handle->writeToBuffer(col, row + header_offset, str, fogColor);

		}

	}

}

// Closes the file stream & resets all variables upon changing map
void closeMap() {
	destroyAI();
	destroyObjects();
	resetSkillStunCharges();
	resetScoreSystem();
	g_Map.clear();
	file.close();
}