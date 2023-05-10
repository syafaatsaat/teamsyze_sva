/******************************************************************************
Filename:    Menu.c
Author(s):   Eric Aw, Zun Sheng

Description/Features:
  All display-related workings and rendering of graphics in the console is
  handled within this file, which clears the screen appropriately and displays
  certain elements in real-time. WindowsHelper-related features are also
  initialised and called here.
******************************************************************************/

#include "Includes.h"
#include "Graphics.h"
#include "Game.h"
#include "Menu.h"
#include "GameStateLevel1.h"
#include "WindowsHelper.h"
#include "Player.h"

/* Initialise the necessary variables and WindowsHelper-related features */
void Graphics_Init()
{
	WindowsHelper_Init();
	
	WindowsHelper_CustomScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
}

/* Render the display of the game according to the different game states */
void Game_Render(float deltaTime)
{
	switch (GetCurrentGameState())
	{
		case GS_DP_INTRO:
			if (GetJustChangedState())
			{
				WindowsHelper_ClearScreen();
				RenderDigiPenIntro();
				SetJustChangedState(false);
			}
			break;

		case GS_MAINMENU_NEWGAME:
			if (GetJustChangedState())
			{
				WindowsHelper_ClearScreen();
				RenderMenuScreen_Cursor_NewGame();
				SetJustChangedState(false);
			}
			break;

		case GS_MAINMENU_INSTRUCTIONS:
			if (GetJustChangedState())
			{
				WindowsHelper_ClearScreen();
				RenderMenuScreen_Cursor_Instructions();
				SetJustChangedState(false);
			}
			break;

		case LEVEL1_GAME:
			if (GetJustChangedState())
			{
				WindowsHelper_ClearScreen();
				GameStateLevel1_Init();
				SetJustChangedState(false);
			}
			break;

		case GS_MAINMENU_QUIT:
			if (GetJustChangedState())
			{
				WindowsHelper_ClearScreen();
				RenderMenuScreen_Cursor_Quit();
				SetJustChangedState(false);
			}
			break;

		case GS_GAMEPLAY:
			if (GetJustChangedState())
			{
				WindowsHelper_ClearScreen();
				// Render the Gameplay
				SetJustChangedState(false);
			}
			break;

		case GS_HELP:
			if (GetJustChangedState())
			{
				WindowsHelper_ClearScreen();
				RenderHelpScreen();
				SetJustChangedState(false);
			}
			break;
	}
}

/* Clean up anything graphics-related and free up used memory */
void Graphics_Exit()
{
	WindowsHelper_Exit();
}