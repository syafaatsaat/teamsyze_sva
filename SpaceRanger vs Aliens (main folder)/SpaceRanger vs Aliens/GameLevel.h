/***********************************************************************************
All content © 2018 DigiPen Institute of Technology Singapore, all rights reserved.

Filename:    GameLevel.c
Author(s):   Syafaat (100%)

Description/Features:
This file handles the rendering of the game screen. The game screen consists
of the level map and the UI. The only function in this file does is to only
print the screen when the player starts the game. The UI consists of the
spaceship's health, the amount of resources(crystals) the player
have, the wave number, the timer and the stores (which is the towers and
the power-ups).
***********************************************************************************/
#pragma once

unsigned char ConvertNumToChar(int num);

void RenderLevelMap(int waveNum, float timer, float shipHealth, int resources);

void Render_Starting_Tutorial(void);

void Render_Flow_Messages(int waveNum, bool isRestTime);

void DisplayStoreMessage(char string[]);

void ResetStoreMsg(void);