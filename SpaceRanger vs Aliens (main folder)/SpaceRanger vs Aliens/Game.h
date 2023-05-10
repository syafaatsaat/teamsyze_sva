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
	GS_GAMEPLAY,
	GS_HELP,
	GS_QUIT
} gameState;

typedef enum
{
	MS_PLAYGAME,
	MS_HELP,
	MS_QUIT
} menuState;

void Game_Init(void);
void Game_Update(float deltaTime);
void Game_Cleanup(void);

bool GetGameRunningState(void);
bool GetJustChangedState(void);
void SetJustChangedState(bool inputState);
gameState GetCurrentGameState(void);