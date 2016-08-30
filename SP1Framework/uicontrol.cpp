#include "uicontrol.h"


unsigned short selected_menu = 0;
unsigned short selected_pause = 0;
unsigned short selected_gameover = 0;
unsigned short selected_Instuction = 0;

extern bool gCanPress;

// Controls logic for Main menu
void updateMainMenu(double eTime, double dTime) {

	static bool keyUp = true;

	if (keyUp) {

		keyUp = false;

		if (isKeyPressed(VK_UP)) {
			if (selected_menu > 0) {
				selected_menu--;
			}
		}
		else if (isKeyPressed(VK_DOWN)) {
			if (selected_menu < 3) {
				selected_menu++;
			}
		}
		// Process selected menu
		if (isKeyPressed(VK_RETURN)) {

			switch (selected_menu) {

			case 0:
				// Start Game
				closeMap();
				current_level = LEVEL_ONE;
				break;

			case 1:
				// Start Instuction Menu
				closeMap();
				selected_Instuction = 0;
				current_level = LEVEL_INSTRUCTION;
				break;

			case 2:
				// Quit
				g_bQuitGame = true;
				break;
			}
		}
	}

	if ((!isKeyPressed(VK_UP)) && (!isKeyPressed(VK_DOWN))) {
		keyUp = true;
	}

}

// Controls logic for Instruction Menu
void updateInstructionMenu(double eTime, double dTime)
{
	static bool canPress = true;

	if (canPress)
	{
		if (isKeyPressed(VK_SPACE))
		{
			if (selected_Instuction == 0)
			{
				closeMap();
				current_level = LEVEL_MENU;
				canPress = false;
			}
			else if (selected_Instuction == 1)
			{
				gCanPress = false;
				g_Map = g_Map_Cache; // Reload the cached map onto the map
				current_level = LEVEL_restart;
				g_eGameState = S_GAME;
				canPress = false;
			}
		}
	}
	canPress = true;
}

void updateWinningMenu(double eTime, double dTime)
{
	static bool canPress = true;

	if (canPress)
	{
		if (isKeyPressed(VK_SPACE))
		{
			closeMap();
			current_level = LEVEL_MENU;
			canPress = false;

		}
	}
	canPress = true;
}

// Controls logic for Pause menu
void updatePauseMenu(double eTime, double dTime) {

	static bool canPress = true;

	if (canPress) {

		canPress = false;

		if (isKeyPressed(VK_UP)) {
			if (selected_pause > 0) {
				selected_pause--;
			}
		}
		else if (isKeyPressed(VK_DOWN)) {
			if (selected_pause < 4) {
				selected_pause++;
			}
		}

		// Process selected menu
		if (isKeyPressed(VK_RETURN)) {

			switch (selected_pause) {

			case 0:
				// Resume
				g_eGameState = S_GAME; // for once, manually set the game state
				g_Map = g_Map_Cache; // Reload the cached map onto the map
				current_level = LEVEL_restart;
				break;

			case 1:
				// Retry
				closeMap();
				current_level = LEVEL_restart;
				break;

			case 2:
				// Instuction
				closeMapOnly();
				selected_Instuction = 1;
				current_level = LEVEL_INSTRUCTION;
				break;
			case 3:
				// Main Menu
				closeMap();
				current_level = LEVEL_MENU;
				break;
			case 4:
				// Quit
				g_bQuitGame = true;
				break;
			}

			selected_pause = 0;

		}

	}

	// Can press again on KeyUp 
	if (!isKeyPressed(VK_UP) && !isKeyPressed(VK_DOWN)) {
		canPress = true;
	}

}

void updateGameOverMenu(double eTime, double dTime) {

	static bool canPress1 = true;

	if (canPress1) {

		canPress1 = false;

		if (isKeyPressed(VK_UP)) {
			if (selected_gameover > 0) {
				selected_gameover--;
			}
		}
		else if (isKeyPressed(VK_DOWN)) {
			if (selected_gameover < 2) {
				selected_gameover++;
			}
		}

		// Process selected menu
		if (isKeyPressed(VK_RETURN)) {

			switch (selected_gameover) {

			case 0:
				// Retry
				closeMap();
				current_level = LEVEL_restart;
				break;

			case 1:
				// Main Menu
				closeMap();
				current_level = LEVEL_MENU;
				break;

			case 2:
				// Quit
				g_bQuitGame = true;
				break;

			}

			selected_gameover = 0;

		}

	}

	// Can press again on KeyUp 
	if (!isKeyPressed(VK_UP) && !isKeyPressed(VK_DOWN)) {
		canPress1 = true;
	}


}

// Draw Main menu to screen
void renderMainMenu(Console * handle) {

	string context1;
	string context2;
	string context3;

	COORD consoleSize = handle->getConsoleSize();

	COORD pos;
	pos.Y = (consoleSize.Y / 2);
	COORD pos2;
	pos2.Y = (consoleSize.Y / 2) + 2;
	COORD pos3;
	pos3.Y = (consoleSize.Y / 2) + 4;

	switch (selected_menu) {

	case 0:
		context1 = ">Start Game<";
		context2 = "Instruction";
		context3 = "Quit";
		break;

	case 1:
		context1 = "Start Game";
		context2 = ">Instruction<";
		context3 = "Quit";
		break;
	case 2:
		context1 = "Start Game";
		context2 = "Instruction";
		context3 = ">Quit<";
		break;

	}

	pos.X = (consoleSize.X / 2) - (context1.length() / 2);
	pos2.X = (consoleSize.X / 2) - (context2.length() / 2);
	pos3.X = (consoleSize.X / 2) - (context3.length() / 2);

	handle->writeToBuffer(pos, context1);
	handle->writeToBuffer(pos2, context2);
	handle->writeToBuffer(pos3, context3);
}

// Draw Pause menu to screen
void renderPauseMenu(Console * handle) {

	string context1;
	string context2;
	string context3;
	string context4;
	string context5;

	COORD consoleSize = handle->getConsoleSize();

	COORD pos;
	pos.Y = (consoleSize.Y / 2);
	COORD pos2;
	pos2.Y = (consoleSize.Y / 2) + 2;
	COORD pos3;
	pos3.Y = (consoleSize.Y / 2) + 4;
	COORD pos4;
	pos4.Y = (consoleSize.Y / 2) + 6;
	COORD pos5;
	pos5.Y = (consoleSize.Y / 2) + 8;

	switch (selected_pause) {

	case 0:
		context1 = ">Resume<";
		context2 = "Retry";
		context3 = "Instruction";
		context4 = "Main Menu";
		context5 = "Quit";
		break;

	case 1:
		context1 = "Resume";
		context2 = ">Retry<";
		context3 = "Instruction";
		context4 = "Main Menu";
		context5 = "Quit";
		break;

	case 2:
		context1 = "Resume";
		context2 = "Retry";
		context3 = ">Instruction<";
		context4 = "Main Menu";
		context5 = "Quit";
		break;

	case 3:
		context1 = "Resume";
		context2 = "Retry";
		context3 = "Instruction";
		context4 = ">Main Menu<";
		context5 = "Quit";
		break;
	case 4:
		context1 = "Resume";
		context2 = "Retry";
		context3 = "Instruction";
		context4 = "Main Menu";
		context5 = ">Quit<";
		break;
	}


	pos.X = (consoleSize.X / 2) - (context1.length() / 2);
	pos2.X = (consoleSize.X / 2) - (context2.length() / 2);
	pos3.X = (consoleSize.X / 2) - (context3.length() / 2);
	pos4.X = (consoleSize.X / 2) - (context4.length() / 2);
	pos5.X = (consoleSize.X / 2) - (context5.length() / 2);

	handle->writeToBuffer(pos, context1);
	handle->writeToBuffer(pos2, context2);
	handle->writeToBuffer(pos3, context3);
	handle->writeToBuffer(pos4, context4);
	handle->writeToBuffer(pos5, context5);
}

void renderGameOverMenu(Console * handle) {

	string context1;
	string context2;
	string context3;

	COORD consoleSize = handle->getConsoleSize();

	COORD pos;
	pos.Y = (consoleSize.Y / 2);
	COORD pos2;
	pos2.Y = (consoleSize.Y / 2) + 2;
	COORD pos3;
	pos3.Y = (consoleSize.Y / 2) + 4;

	switch (selected_gameover) {

	case 0:
		context1 = ">Retry<";
		context2 = "Main Menu";
		context3 = "Quit";
		break;

	case 1:
		context1 = "Retry";
		context2 = ">Main Menu<";
		context3 = "Quit";
		break;

	case 2:
		context1 = "Retry";
		context2 = "Main Menu";
		context3 = ">Quit<";
		break;

	}


	pos.X = (consoleSize.X / 2) - (context1.length() / 2);
	pos2.X = (consoleSize.X / 2) - (context2.length() / 2);
	pos3.X = (consoleSize.X / 2) - (context3.length() / 2);

	handle->writeToBuffer(pos, context1);
	handle->writeToBuffer(pos2, context2);
	handle->writeToBuffer(pos3, context3);

}