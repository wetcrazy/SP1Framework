#include "uicontrol.h"


unsigned short selected_menu = 0;
unsigned short selected_pause = 0;
unsigned short selected_gameover = 0;

// Controls logic for Main menu
void updateMainMenu(double eTime, double dTime) {

	static bool keyUp = false;

	if (keyUp) {

		if (isKeyPressed(VK_UP)) {
			selected_menu = 0;
		}
		else if ((isKeyPressed(VK_UP)) || (isKeyPressed(VK_DOWN)))
		{
			selected_menu = 1;
		}
		else if (isKeyPressed(VK_DOWN)) {
			selected_menu = 2;
		}

		// Process selected menu
		if (isKeyPressed(VK_RETURN)) {

			switch (selected_menu) {

			case 0:
				// Start Game
				closeMap();
				current_level = LEVEL_ONE;
				keyUp = false;
				break;

			case 1:
			{
				// Start Instuction Menu
				closeMap();
				current_level = LEVEL_INSTRUCTION;
				break;
			}
			case 2:
				// Quit
				g_bQuitGame = true;
				break;

			}

		}
	}

	if (!isKeyPressed(VK_RETURN)) {
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
			closeMap();
			current_level = LEVEL_MENU;
			canPress = false;
		}
		canPress = true;
	}
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
			if (selected_pause < 3) {
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
				// Main Menu
				closeMap();
				current_level = LEVEL_MENU;
				break;

			case 3:
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

	COORD consoleSize = handle->getConsoleSize();

	COORD pos;
	pos.Y = (consoleSize.Y / 2);
	COORD pos2;
	pos2.Y = (consoleSize.Y / 2) + 2;
	COORD pos3;
	pos3.Y = (consoleSize.Y / 2) + 4;
	COORD pos4;
	pos4.Y = (consoleSize.Y / 2) + 6;

	switch (selected_pause) {

	case 0:
		context1 = ">Resume<";
		context2 = "Retry";
		context3 = "Main Menu";
		context4 = "Quit";
		break;

	case 1:
		context1 = "Resume";
		context2 = ">Retry<";
		context3 = "Main Menu";
		context4 = "Quit";
		break;

	case 2:
		context1 = "Resume";
		context2 = "Retry";
		context3 = ">Main Menu<";
		context4 = "Quit";
		break;

	case 3:
		context1 = "Resume";
		context2 = "Retry";
		context3 = "Main Menu";
		context4 = ">Quit<";
		break;

	}


	pos.X = (consoleSize.X / 2) - (context1.length() / 2);
	pos2.X = (consoleSize.X / 2) - (context2.length() / 2);
	pos3.X = (consoleSize.X / 2) - (context3.length() / 2);
	pos4.X = (consoleSize.X / 2) - (context4.length() / 2);

	handle->writeToBuffer(pos, context1);
	handle->writeToBuffer(pos2, context2);
	handle->writeToBuffer(pos3, context3);
	handle->writeToBuffer(pos4, context4);

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