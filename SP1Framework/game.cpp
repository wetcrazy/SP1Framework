// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include "map.h"
#include "dialogue.h"
#include "_interactable.h"
#include "_AI.h"
#include "cheat.h"
#include "skills.h"
#include "uicontrol.h"

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

// Game specific variables here
SGameChar g_sChar;
EGAMESTATES g_eGameState;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once


// Console object
Console g_Console(mapWidth, mapHeight + footer_offset, "Group 6");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init(void) {

	// Set precision for floating point output
	g_dElapsedTime = 0.0;
	g_dBounceTime = 0.0;

	// sets the initial state for the game
	g_eGameState = S_TITLESCREEN;
	current_level = LEVEL_TITLE;

	g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
	g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y / 2;
	g_sChar.xP = ' ';
	g_sChar.xN = ' ';
	g_sChar.yP = ' ';
	g_sChar.yN = ' ';
	g_sChar.below = ' ';
	g_sChar.direction = D_UP;

	g_sChar.m_bActive = true;
	g_sChar.m_bStunned = false;

	// sets the width, height and the font name to use in the console
	g_Console.setConsoleFont(10, 18, L"Raster");

}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown(void) {
	// Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	closeMap();
	g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput(void) {
	g_abKeyPressed[K_UP] = isKeyPressed(VK_UP);
	g_abKeyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
	g_abKeyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
	g_abKeyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_F1] = isKeyPressed(VK_F1);
	g_abKeyPressed[K_F2] = isKeyPressed(VK_F2);
	g_abKeyPressed[K_F3] = isKeyPressed(VK_F3);
	g_abKeyPressed[K_F4] = isKeyPressed(VK_F4);
	g_abKeyPressed[K_F5] = isKeyPressed(VK_F5);
	g_abKeyPressed[K_F6] = isKeyPressed(VK_F6);
	g_abKeyPressed[K_F7] = isKeyPressed(VK_F7);
	g_abKeyPressed[K_F8] = isKeyPressed(VK_F8);
	g_abKeyPressed[K_F9] = isKeyPressed(VK_F9);
	g_abKeyPressed[K_F10] = isKeyPressed(VK_F10);
	g_abKeyPressed[K_F11] = isKeyPressed(VK_F11);
	g_abKeyPressed[K_1] = isKeyPressed(0x31);
	g_abKeyPressed[K_2] = isKeyPressed(0x32);
	g_abKeyPressed[K_3] = isKeyPressed(0x33);
	g_abKeyPressed[K_4] = isKeyPressed(0x34);

}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt) {
	// get the delta time
	g_dElapsedTime += dt;
	g_dDeltaTime = dt;

	switch (g_eGameState) {
	case S_PAUSE: updatePauseMenu(g_dElapsedTime, dt);
		break;
	case S_TITLESCREEN: titleScreenWait();
		break;
	case S_MENU: updateMainMenu(g_dElapsedTime, dt);
		break;
	case S_GAME: gameplay(); // gameplay logic when we are in the game
		break;
	case S_GAMEOVER: updateGameOverMenu(g_dElapsedTime, dt);// game logic for gameover
		break;
	}
}
//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render() {
	clearScreen();      // clears the current screen and draw from scratch 
	switch (g_eGameState) {
	case S_PAUSE:
	case S_TITLESCREEN:
	case S_MENU:
	case S_GAME:
	case S_GAMEOVER:
		renderGame();
		break;
	}
	renderFramerate();  // renders debug information, frame rate, elapsed time, etc
	renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void gameplay() // gameplay logic
{
	processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit

	if (current_level != LEVEL_MENU && current_level != LEVEL_PAUSE) {
		updateAI(g_dElapsedTime, g_dDeltaTime); // processs AI logic
		if (current_level != LEVEL_OVER) {
			moveCharacter();    // moves the character, collision detection, physics, etc, sound can be played here too.
			processSkill(g_dDeltaTime);
			updateObjects(&g_Console, current_level, g_dElapsedTime); // update logic for the objects in game
			processcheat(g_abKeyPressed);

		}
	}

}

void moveCharacter() {

	try {

		// Collision Detection
		g_sChar.xP = g_Map.at(g_sChar.m_cLocation.Y).at(g_sChar.m_cLocation.X + 1);
		g_sChar.xN = g_Map.at(g_sChar.m_cLocation.Y).at(g_sChar.m_cLocation.X - 1);
		g_sChar.yP = g_Map.at(g_sChar.m_cLocation.Y - 1).at(g_sChar.m_cLocation.X);
		g_sChar.yN = g_Map.at(g_sChar.m_cLocation.Y + 1).at(g_sChar.m_cLocation.X);
		g_sChar.below = g_Map.at(g_sChar.m_cLocation.Y).at(g_sChar.m_cLocation.X);

	}
	catch (out_of_range ex) {

		// Go next level
		closeMap();
		if (current_level == LEVEL_ONE) {
			current_level = LEVEL_TWO;
		}
		else if (current_level == LEVEL_TWO) {
			current_level = LEVEL_TEN;
		}
		else {
			current_level = LEVEL_TITLE;
		}
	}

	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;

	if (!g_sChar.m_bStunned) {

		// Updating the location of the character based on the key press
		// providing a beep sound whenver we shift the character
		if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 0 && isPassable(g_sChar.yP)) {
			g_sChar.m_cLocation.Y--;
			bSomethingHappened = true;
			g_sChar.direction = D_UP;
		}
		else if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 0 && !isPassable(g_sChar.yP)) {
			Beep(1500, 100);
		}
		else if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0 && isPassable(g_sChar.xN)) {
			g_sChar.m_cLocation.X--;
			bSomethingHappened = true;
			g_sChar.direction = D_LEFT;
		}
		else if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0 && !isPassable(g_sChar.xN)) {
			Beep(1500, 100);
		}
		else if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1 && isPassable(g_sChar.yN)) {

			g_sChar.m_cLocation.Y++;
			bSomethingHappened = true;
			g_sChar.direction = D_DOWN;
		}
		else if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1 && !isPassable(g_sChar.yN)) {
			Beep(1500, 100);
		}
		else if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1 && isPassable(g_sChar.xP)) {
			g_sChar.m_cLocation.X++;
			bSomethingHappened = true;
			g_sChar.direction = D_RIGHT;
		}
		else if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1 && !isPassable(g_sChar.xP)) {
			Beep(1500, 100);
		}

	}

	if (bSomethingHappened) {
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.1; // 125ms should be enough
	}


}
void processUserInput() {
	if (g_abKeyPressed[K_ESCAPE]) {
		closeHalfMap();
		LEVEL_restart = current_level;
		current_level = LEVEL_PAUSE;
	}

}

void clearScreen() {
	// Clears the buffer with this colour attribute
	g_Console.clearBuffer(0x1F);
}

void titleScreenWait() {

	if (isKeyPressed(VK_SPACE)) {
		closeMap();
		current_level = LEVEL_MENU;
	}

}

void renderGame() {
	renderMap(&g_Console);        // renders the map to the buffer first

	switch (current_level) {
	case LEVEL_PAUSE:
		renderPauseMenu(&g_Console);
		break;
	case LEVEL_OVER:
		renderGameOverMenu(&g_Console);
		break;
	case LEVEL_TITLE:
		break;
	case LEVEL_MENU:
		renderMainMenu(&g_Console);
		break;
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
		renderCharacter();  // renders the character into the buffer
		renderFog(&g_Console); // fog on 2nd layer
		renderAI(&g_Console); // we can still see AI even if they are in the fog
		dialogue(&g_Console); // HUD interface
		break;
	}


}


void renderCharacter() {
	// Draw the location of the character
	WORD charColor = g_PlayerColor;
	if (g_sChar.m_bStunned) {
		charColor = g_PlayerColorStunned;
	}
	else if (g_sChar.m_bActive) {
		charColor = g_PlayerColorActive;
	}
	g_Console.writeToBuffer(g_sChar.m_cLocation.X, g_sChar.m_cLocation.Y + header_offset, (char)g_PlayerIcon, charColor);
}


void renderFramerate() {
	COORD c;
	// displays the framerate
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(3);
	ss << 1.0 / g_dDeltaTime << "fps";
	c.X = g_Console.getConsoleSize().X - 9;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str());

	// displays the elapsed time
	ss.str("");
	ss << g_dElapsedTime << "secs";
	c.X = 0;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str());
}
void renderToScreen() {
	// Writes the buffer to the console, hence you will see what you have written
	g_Console.flushBufferToConsole();
}