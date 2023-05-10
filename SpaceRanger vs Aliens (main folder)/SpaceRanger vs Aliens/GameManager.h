/***********************************************************************************
All content © 2018 DigiPen Institute of Technology Singapore, all rights reserved.

Filename:    GameManager.c
Author(s):   Eric (90%) , Syafaat (5%), Ying Ying (5%)

Description/Features:
This file handles the updating and structure of game states within the game,
and is the game state manager for the overall game flow, from when the game
is launched to when the user chooses to quit. There are also functions that
can be called to access or retrieve information regarding the game states.
***********************************************************************************/
#pragma once

#define DP_INTRO_TIME 3.0f

#include "Includes.h"

typedef enum
{
	LEVEL1_GAME,
	GS_DP_INTRO,
	GS_MAINMENU_NEWGAME,
	GS_MAINMENU_INSTRUCTIONS,
	GS_MAINMENU_QUIT,
	GS_HELP,
	GS_QUIT,
	GS_TEAM_INTRO,
	GS_LOSE_GAME,
	GS_WIN_GAME,
	GS_PAUSE_MENU_RESUME,
	GS_PAUSE_MENU_QUIT,
	GS_CREDITS,
	GS_MAINMENU_CREDITS

} gameState;

void Game_Init(void);
void Game_Update(float deltaTime);

bool GetGameRunningState(void);
bool GetJustChangedState(void);
void SetJustChangedState(bool inputState);
gameState GetCurrentGameState(void);