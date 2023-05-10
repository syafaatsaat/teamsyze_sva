/***********************************************************************************
All content © 2018 DigiPen Institute of Technology Singapore, all rights reserved.

Filename:    GraphicsManager.c
Author(s):   Eric Aw, Chua Zun Sheng, Ying Ying

Description/Features:
  All display-related workings and rendering of graphics in the console is
  handled within this file, which clears the screen appropriately and displays
  certain elements in real-time. WindowsHelper-related features are also
  initialised and called here.
***********************************************************************************/

#include "Includes.h"
#include "GraphicsManager.h"
#include "GameManager.h"
#include "Menu.h"
#include "GameStateLevel1.h"
#include "WindowsHelper.h"
#include "Player.h"
#include "GameLevel.h"
#include "Tower.h"
#include "GameOver.h"

/* Initialise the necessary variables and WindowsHelper-related features */
void GraphicsManager_Init(void)
{
	WindowsHelper_Init();
	
	WindowsHelper_CustomScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
}

/* Render the display of the game according to the different game states */
void Game_Render(float deltaTime)
{
	WindowsHelper_SetCursorPosition(0, 0);
	WindowsHelper_ClearBuffer();

	switch (GetCurrentGameState())
	{
		case GS_DP_INTRO:
			RenderDigiPenIntro();
			break;

		case GS_TEAM_INTRO:
			RenderTeamIntro();
			break;

		case GS_MAINMENU_NEWGAME:
			RenderMenuScreen_Cursor_NewGame();
			break;

		case GS_MAINMENU_INSTRUCTIONS:
			RenderMenuScreen_Cursor_Instructions();
			break;

		case LEVEL1_GAME:
			if (GetJustChangedState())
			{
				GameStateLevel1_Init();
				SetJustChangedState(false);
			}
			/* Render the map with information. */
			GameStateLevel1_Update(deltaTime);
			/*Render_Player();*/
			
			break;

		case GS_MAINMENU_QUIT:
			RenderMenuScreen_Cursor_Quit();
			break;

		case GS_HELP:
			RenderHelpScreen();
			break;

		case GS_LOSE_GAME:
			Render_GameOver();
			break;

		case GS_WIN_GAME:
			Render_GameVictory();
			break;

		case GS_PAUSE_MENU_RESUME:
			RenderPauseResumeScreen();
			break;

		case GS_PAUSE_MENU_QUIT:
			RenderPauseQuitScreen();
			break;

		case GS_MAINMENU_CREDITS:
			RenderMenuScreen_Cursor_Credits();
			break;

		case GS_CREDITS:
			RenderCreditsScreen();
			break;

	}
	WindowsHelper_DrawOutputBuffer();
}

/* Clean up anything graphics-related and free up used memory */
void GraphicsManager_Exit(void)
{
	WindowsHelper_Exit();
}