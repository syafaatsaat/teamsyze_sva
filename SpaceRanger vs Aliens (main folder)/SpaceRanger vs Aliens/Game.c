/******************************************************************************
Filename:    Game.c
Author(s):   Eric, Syafaat, Zun Sheng

Description/Features:
  This file handles the updating and structure of game states within the game,
  and is the game state manager for the overall game flow, from when the game
  is launched to when the user chooses to quit. There are also functions that
  can be called to access or retrieve information regarding the game states.
******************************************************************************/

#include "Includes.h"
#include "Game.h"
#include "WindowsHelper.h"
#include "Menu.h"
#include "GameStateLevel1.h"

gameState theGameState;
menuState theMenuState;

float elapsedTime;				/* The amount of time elapsed since the start of the program */
float gameStateElapsedTime;		/* The amount of time elapsed since the start of the current game state */

bool gameRunning;				/* Checks if the game is currently running */
bool gameJustChangedState;		/* Checks if the state of the game has just been changed */

/* Input detection/handling for various keys */
bool upKey_PressedOnce;
bool upKey_PreviouslyDown;
bool downKey_PressedOnce;
bool downKey_PreviouslyDown;
bool enterKey_PressedOnce;
bool enterKey_PreviouslyDown;

/* Initialise the important variables used */
void Game_Init()
{
	theGameState = GS_DP_INTRO;
	theMenuState = MS_PLAYGAME;

	elapsedTime = 0.0f;
	gameStateElapsedTime = 0.0f;

	gameRunning = true;
	gameJustChangedState = true;

	upKey_PressedOnce = false;
	upKey_PreviouslyDown = false;
	downKey_PressedOnce = false;
	downKey_PreviouslyDown = false;
	enterKey_PressedOnce = false;
	enterKey_PreviouslyDown = false;
}

void UpdateTimings(float deltaTime)
{
	elapsedTime += deltaTime;
	gameStateElapsedTime += deltaTime;
}

/* Handles the detection of keyboard inputs, and updates their statuses */
void UpdateKeyboardInput()
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
		if (!enterKey_PreviouslyDown)
		{
			enterKey_PressedOnce = true;

			enterKey_PreviouslyDown = true;
		}
		else
			enterKey_PressedOnce = false;
	}
	else
		enterKey_PreviouslyDown = false;
}

/* Changes the current game state to the desired state*/
void Game_ChangeState(gameState inputGameState)
{
	WindowsHelper_ClearScreen();

	theGameState = inputGameState;

	gameJustChangedState = true;
	
	gameStateElapsedTime = 0.0f;
}

/* Update the game in real-time, in accordance with the current game state */
void Game_Update(float deltaTime)
{
	UpdateTimings(deltaTime);

	UpdateKeyboardInput();

	switch (theGameState)
	{
		case LEVEL1_GAME:
			// Go to GAMEPLAY state IF user selects "Start New Game" in the Main Menu
			GameStateLevel1_Update(deltaTime);
			break;
	
		case GS_DP_INTRO:
			// After the game is launched, be in the DIGIPEN_INTRO state for a fixed amount of time, then go to MAIN_MENU state
			if (gameStateElapsedTime >= DP_INTRO_TIME)
				Game_ChangeState(GS_MAINMENU_NEWGAME);
			break;

		case GS_MAINMENU_NEWGAME:
			// Transition to the Main Menu after intro, and await for user input on the main menu
			if (upKey_PressedOnce)
				Game_ChangeState(GS_MAINMENU_QUIT);
			
			if (downKey_PressedOnce)
				Game_ChangeState(GS_MAINMENU_INSTRUCTIONS);

			if (enterKey_PressedOnce)
				Game_ChangeState(LEVEL1_GAME);
			break;

		case GS_MAINMENU_INSTRUCTIONS:
			// Transition to the Main Menu after intro, and await for user input on the main menu
			if (upKey_PressedOnce)
				Game_ChangeState(GS_MAINMENU_NEWGAME);

			if (downKey_PressedOnce)
				Game_ChangeState(GS_MAINMENU_QUIT);

			//if (enterKey_PressedOnce)
			//	;
			break;

		case GS_MAINMENU_QUIT:
			// Transition to the Main Menu after intro, and await for user input on the main menu
			if (upKey_PressedOnce)
				Game_ChangeState(GS_MAINMENU_INSTRUCTIONS);

			if (downKey_PressedOnce)
				Game_ChangeState(GS_MAINMENU_NEWGAME);

			if (enterKey_PressedOnce)
				Game_ChangeState(GS_QUIT);
			break;

		case GS_GAMEPLAY:
			// Go to GAMEPLAY state IF user selects "Start New Game" in the Main Menu

			break;

		case GS_HELP:
			// Go to HELP_SCREEN state IF user selects "Help" in the Main Menu

			break;

		case GS_QUIT:
			// If user selects "Quit" in the Main Menu, set gameRunning bool to false
			gameRunning = false;
			break;
	}

}

void Game_Cleanup()
{

}

/* Return the boolean that keeps track of when the game is running */
bool GetGameRunningState()
{
	return gameRunning;
}

/* Return the boolean that keeps track of when the game state has just been changed */
bool GetJustChangedState()
{
	return gameJustChangedState;
}

/* Allows the boolean "gameJustChangedState" to be set  */
void SetJustChangedState(bool inputState)
{
	gameJustChangedState = inputState;
}

/* Returns the current game state */
gameState GetCurrentGameState()
{
	return theGameState;
}