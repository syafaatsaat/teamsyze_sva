/***********************************************************************************
All content © 2018 DigiPen Institute of Technology Singapore, all rights reserved.

Filename:    GameStateLevel1.h
Author(s):   Syafaat (95%), Eric (5%)

Description/Features:
This file handles the updating and structure of Level 1, from when the game
is launched to when the user chooses to quit. The enemy is initialized in this
file and their functions are in another file to function the enemies. The player
functions are called here and every aspect of the gameplay is binded together
here.
***********************************************************************************/
#pragma once

void GameStateLevel1_Init(void);
void GameStateLevel1_Update(float dt);
bool GameStateLevel1_Exit(void);
bool GameStateLevel1_VictoryStatus(void);
void Game_GameQuit(void);
bool GameStateLevel1_Quit(void);
void Game_Paused(void);
void Game_Unpaused(void);
bool retGame_Paused(void);
void Game_QuitResume(void);
bool retGame_QuitResume(void);
float *GetShipHealthPtr(void);
int *GetResourcesPtr(void);
float GetLevelTime(void);
int GetWaveNum(void);

void Instruction_Paused(void);
void Instruction_Unpaused(void);
bool retInstruction_Paused(void);