#ifndef _UICONTROL_H
#define _UICONTROL_H


#include "Framework\console.h"
#include "map.h"




// Controls logic for Main menu
void updateMainMenu(double eTime, double dTime);

// Controls logic for Pause menu
void updatePauseMenu(double eTime, double dTime);

// Controls logic for Game Over menu
void updateGameOverMenu(double eTime, double dTime);

// Draw Main menu to screen
void renderMainMenu(Console * handle);

// Draw Pause menu to screen
void renderPauseMenu(Console * handle);

// Draw Game Over menu to screen
void renderGameOverMenu(Console * handle);



#endif