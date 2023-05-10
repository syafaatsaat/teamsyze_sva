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

#include "Includes.h"
#include "GameManager.h"
#include "WindowsHelper.h"
#include "Menu.h"
#include "GameStateLevel1.h"

gameState theGameState;

float elapsedTime;				/* The amount of time elapsed since the start of the program */
float gameStateElapsedTime;		/* The amount of time elapsed since the start of the current game state */

bool gameRunning;				/* Checks if the game is currently running */
bool gameJustChangedState;		/* Checks if the state of the game has just been changed */

/* Input detection/handling for various keys */
bool upKey_PressedOnce;
bool upKey_PreviouslyDown;
bool downKey_PressedOnce;
bool downKey_PreviouslyDown;
bool GMenterKey_PressedOnce;
bool GMenterKey_PreviouslyDown;
bool GMescKey_PressedOnce;
bool GMescKey_PreviouslyDown;


/* Initialise the important variables used */
void Game_Init(void)
{
	theGameState = GS_DP_INTRO;

	elapsedTime = 0.0f;
	gameStateElapsedTime = 0.0f;

	gameRunning = true;
	gameJustChangedState = true;

	upKey_PressedOnce = false;
	upKey_PreviouslyDown = false;
	downKey_PressedOnce = false;
	downKey_PreviouslyDown = false;
	GMenterKey_PressedOnce = false;
	GMenterKey_PreviouslyDown = false;
	GMescKey_PressedOnce = false;
	GMescKey_PreviouslyDown = false;
}

void UpdateTimings(float deltaTime)
{
	elapsedTime += deltaTime;
	gameStateElapsedTime += deltaTime;
}

/* Handles the detection of keyboard inputs, and updates their statuses */
void UpdateKeyboardInput(void)
{
	if (GetAsyncKeyState(VK_UP) < 0)
	{
		if (!upKey_PreviouslyDown)
		{
			upKey_PressedOnce = true;

			upKey_PreviouslyDown = true;
		}
		else
			upKey_PressedOnce = false;
	}
	else
		upKey_PreviouslyDown = false;

	if (GetAsyncKeyState(VK_DOWN) < 0)
	{
		if (!downKey_PreviouslyDown)
		{
			downKey_PressedOnce = true;

			downKey_PreviouslyDown = true;
		}
		else
			downKey_PressedOnce = false;
	}
	else
		downKey_PreviouslyDown = false;

	if (GetAsyncKeyState(VK_RETURN) < 0)
	{
		if (!GMenterKey_PreviouslyDown)
		{
			GMenterKey_PressedOnce = true;

			GMenterKey_PreviouslyDown = true;
		}
		else
			GMenterKey_PressedOnce = false;
	}
	else
		GMenterKey_PreviouslyDown = false;

	if (GetAsyncKeyState(VK_ESCAPE) < 0)
	{
		if (!GMescKey_PreviouslyDown)
		{
			GMescKey_PressedOnce = true;

			GMescKey_PreviouslyDown = true;
		}
		else
			GMescKey_PressedOnce = false;
	}
	else
		GMescKey_PreviouslyDown = false;
}

/* Changes the current game state to the desired state*/
void Game_ChangeState(gameState inputGameState)
{
	theGameState = inputGameState;

	gameJustChangedState = true;
	
	gameStateElapsedTime = 0.0f;
}

/* Update the game in real-time, in accordance with the current game state */
void Game_Update(float deltaTime)
{
	UpdateTimings(deltaTime);

	if (theGameState != LEVEL1_GAME)
		UpdateKeyboardInput();

	switch (theGameState)
	{
		case LEVEL1_GAME:
			/* Go to GAMEPLAY state IF user selects "Start New Game" in the Main Menu */
			GameStateLevel1_Update(deltaTime);
			if(GameStateLevel1_Exit())
				Game_ChangeState(GS_LOSE_GAME);
			if(GameStateLevel1_VictoryStatus())
				Game_ChangeState(GS_WIN_GAME);
			if(GameStateLevel1_Quit())
				Game_ChangeState(GS_MAINMENU_NEWGAME);
			break;
	
		case GS_DP_INTRO:
			/*After the game is launched, be in the DIGIPEN_INTRO state for a fixed amount of time, then go to MAIN_MENU state */
			if (gameStateElapsedTime >= DP_INTRO_TIME)
				Game_ChangeState(GS_TEAM_INTRO);
			break;

		case GS_TEAM_INTRO:
			/*After the game is launched, be in the DIGIPEN_INTRO state for a fixed amount of time, then go to MAIN_MENU state */
			if (gameStateElapsedTime >= DP_INTRO_TIME)
				Game_ChangeState(GS_MAINMENU_NEWGAME);
			break;

		case GS_MAINMENU_NEWGAME:
			/* Transition to the Main Menu after intro, and await for user input on the main menu */
			if (upKey_PressedOnce)
				Game_ChangeState(GS_MAINMENU_QUIT);
			
			if (downKey_PressedOnce)
				Game_ChangeState(GS_MAINMENU_INSTRUCTIONS);

			if (GMenterKey_PressedOnce)
			{
				GMenterKey_PressedOnce = false;

				Game_ChangeState(LEVEL1_GAME);
			}
			break;

		case GS_MAINMENU_INSTRUCTIONS:
			/* Transition to the Main Menu after intro, and await for user input on the main menu */
			if (upKey_PressedOnce)
				Game_ChangeState(GS_MAINMENU_NEWGAME);

			if (downKey_PressedOnce)
				Game_ChangeState(GS_MAINMENU_CREDITS);

			if (GMenterKey_PressedOnce)
				Game_ChangeState(GS_HELP);
			break;

		case GS_MAINMENU_CREDITS:
			/* Transition to the Main Menu after intro, and await for user input on the main menu */
			if (upKey_PressedOnce)
				Game_ChangeState(GS_MAINMENU_INSTRUCTIONS);

			if (downKey_PressedOnce)
				Game_ChangeState(GS_MAINMENU_QUIT);

			if (GMenterKey_PressedOnce)
				Game_ChangeState(GS_CREDITS);
			break;

		case GS_MAINMENU_QUIT:
			/* Transition to the Main Menu after intro, and await for user input on the main menu */
			if (upKey_PressedOnce)
				Game_ChangeState(GS_MAINMENU_CREDITS);

			if (downKey_PressedOnce)
				Game_ChangeState(GS_MAINMENU_NEWGAME);

			if (GMenterKey_PressedOnce)
				Game_ChangeState(GS_QUIT);
			break;

		case GS_HELP:
			if (GMescKey_PressedOnce || GMenterKey_PressedOnce)
				Game_ChangeState(GS_MAINMENU_NEWGAME);
			break;

		case GS_QUIT:
			/* If user selects "Quit" in the Main Menu, set gameRunning bool to false */
			gameRunning = false;
			break;

		case GS_LOSE_GAME:
			if (GMescKey_PressedOnce || GMenterKey_PressedOnce)
				Game_ChangeState(GS_MAINMENU_NEWGAME);
			break;

		case GS_WIN_GAME:
			if (GMescKey_PressedOnce || GMenterKey_PressedOnce)
				Game_ChangeState(GS_MAINMENU_NEWGAME);
			break;

		case GS_PAUSE_MENU_RESUME:
			if (downKey_PressedOnce|| upKey_PressedOnce)
				Game_ChangeState(GS_PAUSE_MENU_QUIT);
			if (GMenterKey_PressedOnce || GMescKey_PressedOnce)
				Game_ChangeState(LEVEL1_GAME);
			break;

		case GS_PAUSE_MENU_QUIT:
			if (downKey_PressedOnce || upKey_PressedOnce)
				Game_ChangeState(GS_PAUSE_MENU_RESUME);
			if (GMenterKey_PressedOnce)
				Game_ChangeState(GS_LOSE_GAME);
			break;

		case GS_CREDITS:
			if (GMescKey_PressedOnce || GMenterKey_PressedOnce)
				Game_ChangeState(GS_MAINMENU_NEWGAME);
			break;
	}

}

/* Return the boolean that keeps track of when the game is running */
bool GetGameRunningState(void)
{
	return gameRunning;
}

/* Return the boolean that keeps track of when the game state has just been changed */
bool GetJustChangedState(void)
{
	return gameJustChangedState;
}

/* Allows the boolean "gameJustChangedState" to be set  */
void SetJustChangedState(bool inputState)
{
	gameJustChangedState = inputState;
}

/* Returns the current game state */
gameState GetCurrentGameState(void)
{
	return theGameState;
}