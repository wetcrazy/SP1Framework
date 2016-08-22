#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

using namespace std;

extern double  g_dElapsedTime;
extern CStopWatch g_swTimer;
extern bool g_bQuitGame;
const char g_PlayerIcon = (char)1;
const WORD g_PlayerColor = 0xF0;
const WORD g_PlayerColorActive = 0x50;
const WORD g_PlayerColorDamaged = 0x40;

// Enumeration to store the control keys that your game will have
enum EKEYS {
	K_UP,
	K_DOWN,
	K_LEFT,
	K_RIGHT,
	K_ESCAPE,
	K_SPACE,
	K_F1,
	K_F2,
	K_F3,
	K_F4,
	K_F5,
	K_F6,
	K_F7,
	K_F8,
	K_F9,
	K_F10,
	K_F11,
	K_1,
	K_2,
	K_3,
	K_COUNT

};

// Enumeration for the different screen states
enum EGAMESTATES {
	S_TITLESCREEN,
	S_MENU,
	S_GAME,
	S_GAMEOVER,
	S_COUNT
};

// struct for the game character
struct SGameChar {
	COORD m_cLocation;
	bool  m_bActive;
	char  xP;
	char  xN;
	char  yP;
	char  yN;
	char  below;
};

extern SGameChar g_sChar;

void gameover();
void renderArrow(void);// arrow for menu
void init(void);      // initialize your variables, allocate memory, etc
void getInput(void);      // get input from player
void update(double dt); // update the game and the state of the game
void render(void);      // renders the current state of the game to the console
void shutdown(void);      // do clean up, free memory
void titleScreenWait();// wait for time to pass in title screen
void MenuScreenWait();    // waits for time to pass in splash screen
void gameplay();            // gameplay logic
void moveCharacter();       // moves the character, collision detection, physics, etc
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 
void renderTitleScreen() ;//renders the title screen
void renderMenuScreen();  // renders the splash screen
void renderGame();          // renders the game stuff
void renderMap();           // renders the map to the buffer first
void renderCharacter();     // renders the character into the buffer
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game

#endif // _GAME_H