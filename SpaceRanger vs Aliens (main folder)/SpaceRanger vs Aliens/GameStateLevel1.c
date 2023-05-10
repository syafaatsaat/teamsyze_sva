/***********************************************************************************
All content © 2018 DigiPen Institute of Technology Singapore, all rights reserved.

Filename:    GameStateLevel1.c
Author(s):   Syafaat (95%), Eric (5%)

Description/Features:
  This file handles the updating and structure of Level 1, from when the game
  is launched to when the user chooses to quit. The enemy is initialized in this
  file and their functions are in another file to function the enemies. The player
  functions are called here and every aspect of the gameplay is binded together
  here.
***********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "WindowsHelper.h"
#include "Player.h"
#include "Enemy.h"
#include "GameLevel.h"
#include "GameStateLevel1.h"
#include "Menu.h"
#include "Weapon.h"
#include "Tower.h"
#include "GamePause.h"


/* Array of structs that holds the different information of the enemies. */
Enemy enemy[ENEMY_WAVE_SIZE] =
{
	{ 0 }
};

/* The game time is initialized at LEVEL_TIME_MAX (8 minutes). 
   This is basically the duration of the entire game. */
float levelTime = LEVEL_TIME_MAX;

/* The ship health is initialized at SHIP_MAX_HEALTH. */
float shipHealth = SHIP_MAX_HEALTH;

/* The amount of resources (crystals) that the player has
   which is used to buy things from the store. */
int resources = RESOURCES_STARTING_AMT;

/* The wave time is initialized at WAVE_TIME_MAX (2 minutes).
   This is basically the duration of each wave. */
float waveTime = WAVE_TIME_MAX;
/* The rest time is initialized at REST_TIME_MAX (1 minute).
   This is basically the duration of each rest after each wave. */
float restTime = REST_TIME_MAX;

/* The waveNum holds the number of waves the game has gone through. */
int waveNum;

bool tutorialState; /* Holds information if the game is in tutorial screen or not. */
bool isGameOver; /* Holds information if the game is over or not. */
bool isGameQuit; /* Holds information if player quits or not. */
bool isGamePaused; /* Holds information if the game is paused or not. */
bool isInstructionPaused; /* Holds information if the game is paused or not. */
bool isQuitOrResume; /* if false, resume. if true, quit */
bool weSurvived; /* Holds information if the game is over with player surviving through it or not. */
bool isRestTime; /* Holds information if the wave is over and rest time is on or not. */

/* Initializes game. */
void GameStateLevel1_Init(void)
{
	/* initializes everything once more. */
	levelTime = LEVEL_TIME_MAX;
	shipHealth = SHIP_MAX_HEALTH;
	resources = RESOURCES_STARTING_AMT;
	waveTime = WAVE_TIME_MAX;
	restTime = REST_TIME_MAX;

	/* initializes waveNum to start at 1. */
	waveNum = 1;

	/* Sets up the console window things. */
	WindowsHelper_Init();

	/* Renders the tutorial screen. */
	Render_Starting_Tutorial();

	/* Initialise the player. */
	Player_Init();

	/* Initialise the enemy one by one.*/
	for (int i = 0; i < ENEMY_WAVE_SIZE; ++i)
	{
		Enemy_Init(i, &enemy[i]);
	}

	/* initializes all the boolean variables. */
	isGameOver = false;
	isGameQuit = false;
	isGamePaused = false;
	isQuitOrResume = false;
	tutorialState = true;
	weSurvived = false;
	isRestTime = false;
}

/* Called every frame/time after GameStateLevel1_Init(). */
void GameStateLevel1_Update(float dt)
{
	/* if the game is at the tutorial screen */
	if (tutorialState)
	{
		/* keep rendering the tutorial screen */
		Render_Starting_Tutorial();

		/* if there is a SPACE keypress, start the game officially by toggling the tutorialState */
		if (GetAsyncKeyState(VK_SPACE) < 0)
		{
			tutorialState = false;
		}
	}
	else
	{
		/* if the game is paused */
		if (isGamePaused)
		{
			/* do update the player to detect any keyboard inputs */
			Player_Update(dt);

			/* this is to just render the respective YES or NO options screen to quit or resume */
			if (isQuitOrResume)
			{
				RenderPauseQuitScreen();
			}
			else
			{
				RenderPauseResumeScreen();
			}
		}
		else if (isInstructionPaused)
		{
			/* do update the player to detect any keyboard inputs */
			Player_Update(dt);

			RenderInGameHelpScreen();
		}
		else /* else if the game is not paused and running */
		{
			/* checking if the shipHealth is still not zero (alive) and the levelTime has run out */
			if (shipHealth > 0 && levelTime <= 0)
			{
				/* set weSurvived to true, that triggers the rendering of victory screen in GameManager.c */
				weSurvived = true;
			}

			/* checking if the shipHealth is still not zero (alive) and the levelTime is still not zero (still running)
			   basically, checking if the game is still ongoing */
			if (shipHealth > 0 && levelTime > 0)
			{
				/* decrement the levelTime every second */
				levelTime -= (float)(0.5 * dt);

				/* checking if it is rest time or not */
				if (!isRestTime)
				{
					/* if it is not rest time, that means the wave is ongoing and we decrement waveTime every second */
					waveTime -= (float)(0.5 * dt);
					/* we render the level map with the appropriate information */
					RenderLevelMap(waveNum, waveTime, shipHealth, resources);

					/* for the first five seconds of the wave, we display the wave starting message */
					if (waveTime <= 120.f && waveTime >= 115.f)
					{
						Render_Flow_Messages(waveNum, isRestTime);
					}

					/* if the wave time has run out, we transition to rest time */
					if (waveTime <= 0.f)
					{
						restTime = REST_TIME_MAX;
						isRestTime = true;

						ResetStoreMsg();
					}
				}
				else
				{
					/* if it is rest time, that means the wave has stopped and we decrement restTime every second*/
					restTime -= (float)(0.5 * dt);
					/* we render the level map with the appropriate information */
					RenderLevelMap(waveNum, restTime, shipHealth, resources);

					/* for the first five seconds of the rest time, we display the rest time starting message */
					if (restTime <= 60.f && restTime >= 55.f)
					{
						Render_Flow_Messages(waveNum, isRestTime);
					}

					/* if the rest time has run out, we transition to starting the next wave */
					if (restTime <= 0.f)
					{
						waveNum++;
						waveTime = WAVE_TIME_MAX;
						isRestTime = false;

						ResetStoreMsg();
					}
				}

				/* setting resources to get as low as zero only */
				if (resources < 0)
					resources = 0;

				/* Move the player if there is any player movement, and render the new position. */
				Player_Update(dt);
				Render_Player();
				
				/* Updates the behaviour of towers and renders them */
				towerUpdate(dt);
				renderTower();

				/* Handles the enemy one by one.*/
				for (int i = 0; i < ENEMY_WAVE_SIZE; ++i)
				{
					Enemy_Update(&levelTime, &enemy[i], Player_Bullet, &resources, &shipHealth, dt);
				}
			}
			else /* if the ship health gets to zero, we die and the game is over */
			{
				/* set isGameOver to true, that triggers the rendering of losing screen in GameManager.c */
				isGameOver = true;
			}
		}		
	}
}

/* Returns the state of isGameOver */
bool GameStateLevel1_Exit(void)
{
	return isGameOver;
}

/* Returns the state of weSurvived */
bool GameStateLevel1_VictoryStatus(void)
{
	return weSurvived;
}

/* Setting the state of isGameQuit to true */
void Game_GameQuit(void)
{
	isGameQuit = true;
}

/* Returns the state of isGameQuit */
bool GameStateLevel1_Quit(void)
{
	return isGameQuit;
}

/* Setting the state of isGamePaused to true */
void Game_Paused(void)
{
	isGamePaused = true;
}

/* Setting the state of isGamePaused to false */
void Game_Unpaused(void)
{
	isGamePaused = false;
}

/* Returns the state of isGamePaused */
bool retGame_Paused(void)
{
	return isGamePaused;
}

/* Setting the state of isGamePaused to true */
void Instruction_Paused(void)
{
	isInstructionPaused = true;
}

/* Setting the state of isGamePaused to false */
void Instruction_Unpaused(void)
{
	isInstructionPaused = false;
}

/* Returns the state of isGamePaused */
bool retInstruction_Paused(void)
{
	return isInstructionPaused;
}

/* Toggling the state of isQuitOrResume */
void Game_QuitResume(void)
{
	isQuitOrResume = !isQuitOrResume;
}

/* Returns the state of isQuitOrResume */
bool retGame_QuitResume(void)
{
	return isQuitOrResume;
}

/* Returns the shipHealth */
float *GetShipHealthPtr(void)
{
	return &shipHealth;
}

/* Returns the number of resources */
int *GetResourcesPtr(void)
{
	return &resources;
}

/* Returns the level time */
float GetLevelTime(void)
{
	return levelTime;
}

/* Returns the wave number */
int GetWaveNum(void)
{
	return waveNum;
}