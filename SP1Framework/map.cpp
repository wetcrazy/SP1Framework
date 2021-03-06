﻿#include "map.h"
#include "_interactable.h" 
#include "score.h"
#include "bullet.h"


static ifstream file;

MAP LEVEL_restart;
MAP current_level;

vector< vector<char> > g_Map;
vector< vector<char> > g_Map_Cache;

short fogWidth = 8;
short fogHeight = 4;

const WORD mapColor = 0xF8;
const WORD fogColor = 0x0F;
const WORD menuColor = 0x0F;
const WORD level3WallColor = 0xF0;

const unsigned char mapWalls = 0xDB;

void renderMap(Console *handle) {

	string buffer; // Buffer that contains the line of string that we read from the text file

	// Load map if it is not currently loaded
	if (!file.is_open()) {
		switch (current_level) {
		case LEVEL_WON:
			file.open("maps/level_" + to_string(current_level) + ".txt");
			g_eGameState = S_WON;
			break;
		case LEVEL_PAUSE:
			file.open("maps/level_" + to_string(current_level) + ".txt");
			g_eGameState = S_PAUSE;
			break;
		case LEVEL_OVER:
			file.open("maps/level_" + to_string(current_level) + ".txt");
			g_eGameState = S_GAMEOVER;
			break;
		case LEVEL_TITLE:
			file.open("maps/level_" + to_string(current_level) + ".txt");
			g_eGameState = S_TITLESCREEN;
			break;
		case LEVEL_MENU:
			file.open("maps/level_" + to_string(current_level) + ".txt");
			g_eGameState = S_MENU;
			break;
		case LEVEL_INSTRUCTION:
			file.open("maps/level_" + to_string(current_level) + ".txt");
			g_eGameState = S_INSTRUCTION;
			break;
		case LEVEL_ONE:
			g_sChar.m_cLocation = handle->getConsoleSize(); // Spawn player at middle
			g_sChar.m_cLocation.X /= 2;
			g_sChar.m_cLocation.Y /= 2;
			_POINTS_ASTERISK = _POINTS_ASTERISK_DEFAULT_LEVEL_ONE;
			g_eGameState = S_GAME;
			file.open("maps/level_" + to_string(current_level) + ".txt");
			break;
		case LEVEL_TWO:
			g_sChar.m_cLocation = handle->getConsoleSize(); // Spawn player at middle
			g_sChar.m_cLocation.X /= 2;
			g_sChar.m_cLocation.Y /= 2;
			_POINTS_ASTERISK = _POINTS_ASTERISK_DEFAULT_LEVEL_TWO;
			g_eGameState = S_GAME;
			file.open("maps/level_" + to_string(current_level) + ".txt");
			break;
		case LEVEL_THREE:
			_POINTS_ASTERISK = _POINTS_ASTERISK_DEFAULT_LEVEL_THREE;
			g_sChar.m_cLocation = handle->getConsoleSize();
			g_sChar.m_cLocation.X /= 2;
			(g_sChar.m_cLocation.Y /= 2) += 9; // hard coded y offset

			g_eGameState = S_GAME;
			file.open("maps/level_" + to_string(current_level) + ".txt");
			break;
		case LEVEL_FOUR:
			_POINTS_ASTERISK = _POINTS_ASTERISK_DEFAULT_LEVEL_FOUR;
			g_eGameState = S_GAME;
			file.open("maps/level_" + to_string(current_level) + ".txt");
			break;
		case LEVEL_FIVE:
			g_sChar.m_cLocation = handle->getConsoleSize();
			g_sChar.m_cLocation.X /= 2;
			(g_sChar.m_cLocation.Y /= 2) += 9; // hard coded y offset
			_POINTS_ASTERISK = _POINTS_ASTERISK_DEFAULT_LEVEL_FIVE;
			g_eGameState = S_GAME;
			file.open("maps/level_" + to_string(current_level) + ".txt");
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

					if (buffer[col] == I_TRAP) {
						_COLLECTION_OBJ_TRAP.push_back(TRAP{
							_COLLECTION_OBJ_TRAP.size(), pos, true
						});
					}

					if (buffer[col] == AI::GHOST) {

						buffer[col] = ' '; // Remove the ghost and let AI.cpp manually control it

						_COLLECTION_AI_GHOST.push_back(AI_GHOST{
							_COLLECTION_AI_GHOST.size(), pos, true
						});
					}

					break;

				case LEVEL_THREE:
					if (buffer[col] == AI::GHOST) {

						buffer[col] = '7'; // Remove the ghost and let AI.cpp manually control it

						_COLLECTION_AI_GHOST.push_back(AI_GHOST{
							_COLLECTION_AI_GHOST.size(), pos, true
						});
					}
					break;
				case LEVEL_FOUR:
					if (buffer[col] == I_PORTAL) {
						_COLLECTION_OBJ_PORTAL.push_back(PORTAL{
							_COLLECTION_OBJ_PORTAL.size(), pos, true
						});
					}
					if (buffer[col] == AI::GHOST) {

						buffer[col] = '7'; // Remove the ghost and let AI.cpp manually control it

						_COLLECTION_AI_GHOST.push_back(AI_GHOST{
							_COLLECTION_AI_GHOST.size(), pos, true
						});
					}
					break;
				case LEVEL_FIVE:

					if (buffer[col] == I_SHIELD) {
						_COLLECTION_OBJ_SHIELD_COUNT++;
					}

					if (buffer[col] == AI::BOSS) {
						buffer[col] = ' '; // Remove the boss, let AI.CPP manually control it
						spawn_boss(pos); // Initialize the boss
					}
					break;

				}
			}

			vecRowBuffer.push_back(buffer[col]);
		}

		g_Map.push_back(vecRowBuffer);
		row++;

	}

	char charToPrint;

	// Output everything in g_Map to Console
	for (size_t row = 0; row < g_Map.size(); row++) {
		for (size_t col = 0; col < g_Map.at(row).size(); col++) {

			WORD colorToPrint = mapColor;

			char currentChar = g_Map.at(row).at(col);

			if (current_level == LEVEL_MENU || current_level == LEVEL_TITLE || current_level == LEVEL_PAUSE || current_level == LEVEL_OVER || current_level == LEVEL_INSTRUCTION || current_level == LEVEL_WON) {
				colorToPrint = menuColor;
			}
			else {
				// Color the interactive objects
				switch (currentChar) {

				case I_STAR:
					colorToPrint = bulletPlayerColor;
					break;

				case I_TRAP:
					colorToPrint = _OBJ_TRAP_COLOR;
					break;

				case I_EXIT_ACTIVE:
					colorToPrint = _OBJ_EXIT_COLOR_ACTIVE;
					break;

				case I_EXIT_INACTIVE:
					colorToPrint = _OBJ_EXIT_COLOR_INACTIVE;
					break;

				case I_PORTAL:
					colorToPrint = _OBJ_PORTAL_COLOR;
					break;

				}
			}

			// Change '8' to a mazey character
			if ((currentChar == '8' || currentChar == '7') && current_level != LEVEL_INSTRUCTION) {
				charToPrint = mapWalls;
				if (current_level == LEVEL_THREE || current_level == LEVEL_FOUR) {
					colorToPrint = level3WallColor;
				}
			}
			else {
				charToPrint = currentChar;
			}

			g_Map[row][col] = currentChar;


			handle->writeToBuffer(col, row + header_offset, charToPrint, colorToPrint);
		}
	}

}

void renderFog(Console * handle) {

	string str = " ";

	if ((!isGhostStunned() || _AI_BOSS.phase == 1) && _AI_BOSS.phase < 2){

		for (short row = 0; row < g_Map.size(); row++) {

			for (short col = 0; col < g_Map[row].size(); col++) {

				COORD playerPos = g_sChar.m_cLocation;

				// Skip printing of fog if it falls within the player's vision radius
				if (playerPos.X >= (col - fogWidth) && playerPos.X <= (col + fogWidth) && playerPos.Y <= (row + fogHeight) && playerPos.Y >= (row - fogHeight)) {
					continue;
				}

				// Dont apply fog to the exits/shield/boss
				if (g_Map[row][col] == I_EXIT_INACTIVE || g_Map[row][col] == I_EXIT_ACTIVE || g_Map[row][col] == I_SHIELD || g_Map[row][col] == BOSS) {
					continue;
				}

				handle->writeToBuffer(col, row + header_offset, str, fogColor);

			}

		}

	}
}

void replaceMapCharacterOnce(char c, char sub) {

	for (size_t i = 0; i < g_Map.size(); i++) {
		for (size_t k = 0; k < g_Map[i].size(); k++) {
			if (g_Map[i][k] == c) {
				g_Map[i][k] = sub;
				return;
			}
		}
	}

}

void replaceMapCharacterAll(char c, char sub) {
	for (size_t i = 0; i < g_Map.size(); i++) {
		for (size_t k = 0; k < g_Map[i].size(); k++) {
			if (g_Map[i][k] == c) {
				g_Map[i][k] = sub;
			}
		}
	}
}

void setFogSize(short) {

}

// Closes the file stream & resets all variables upon changing map
void closeMap() {
	destroyAI();
	destroyObjects();
	resetSkillStunCharges();
	destroyAllBullet(); 
	g_sChar.m_bStunned = false;
	g_Map.clear();
	file.close();
}

// For pause menu
void closeHalfMap() {
	g_Map_Cache = g_Map;
	g_Map.clear();
	file.close();
}


void closeMapOnly() {
	if (g_Map.size() > 0) {
		g_Map.clear();
	}
	if (file.is_open()) {
		file.close();
	}

}