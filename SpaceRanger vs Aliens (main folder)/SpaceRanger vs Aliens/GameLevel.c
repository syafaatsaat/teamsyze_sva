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

#include <stdio.h>
#include <stdlib.h>
#include "WindowsHelper.h"
#include "Store.h"
#include "GameLevel.h"
#include "Player.h"

float store_msg_disp_start;
float theTimer;
char store_msg[40] = {0};
TextColour shipHealthColour;

/* Convert the integer digits to char to be displayed properly on the screen. */
unsigned char ConvertNumToChar(int num)
{
	switch (num)
	{
	case 0:
		return '0';
	case 1:
		return '1';
	case 2:
		return '2';
	case 3:
		return '3';
	case 4:
		return '4';
	case 5:
		return '5';
	case 6:
		return '6';
	case 7:
		return '7';
	case 8:
		return '8';
	case 9:
		return '9';
	}

	return 0;
}

/* Render the level map, (for now, still WIP) taking in the level number and timer. */
void RenderLevelMap(int waveNum, float timer, float shipHealth, int resources)
{
	/* To get the time in minutes and seconds. */
	int minutes = 0, seconds = 0, miniSeconds = 0;
	minutes = (int)timer / 60;
	seconds = (int)timer % 60;
	miniSeconds = seconds % 10;
	seconds /= 10;

	/* Print the game screen as a whole. */
	char UI[][151] = { {
		"ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ" },
	{	"ÛÛÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»                                                                                                                                   ÛÛ"},
	{	"ÛÛ    Ñ         º * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *               ÛÛ"},
	{	"ÛÛ    ÃÄÄÄÄÄÄÄÄÄ¶             *             *             *                                                                                         ÛÛ"},
	{	"ÛÛ    ³  ÉÍ Í»  º             *             *             *                                                                                         ÛÛ"},
	{	"ÛÛ  þ ³    ®    º             *             *             *                                                                                         ÛÛ"},
	{	"ÛÛ    ³  ÈÍ Í¼  º * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *               ÛÛ"},
	{	"ÛÛ    ÃÄÄÄÄÄÄÄÄÄ¶             *             *             *                                                                                         ÛÛ"},
	{	"ÛÛ    Ï    ³    º             *             *             *                                                                                         ÛÛ"},
	{	"ÛÛ         ³    º             *             *             *                                                                                         ÛÛ"},
	{	"ÛÛ         ³    º * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *               ÛÛ"},
	{	"ÛÛ    Ñ    ³    º             *             *             *                                                                                         ÛÛ"},
	{	"ÛÛ    ÃÄÄÄÄÄÄÄÄÄ¶             *             *             *                                                                                         ÛÛ"},
	{	"ÛÛ    ³  ÉÍ Í»  º             *             *             *                                                                                         ÛÛ"},
	{	"ÛÛ  þ ³    ®    º * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *               ÛÛ"},
	{	"ÛÛ    ³  ÈÍ Í¼  º             *             *             *                                                                                         ÛÛ"},
	{	"ÛÛ    ÃÄÄÄÄÄÄÄÄÄ¶             *             *             *                                                                                         ÛÛ"},
	{	"ÛÛ    Ï    ³    º             *             *             *                                                                                         ÛÛ"},
	{	"ÛÛ         ³    º * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *               ÛÛ"},
	{	"ÛÛ         ³    º             *             *             *                                                                                         ÛÛ"},
	{	"ÛÛ    Ñ    ³    º             *             *             *                                                                                         ÛÛ"},
	{	"ÛÛ    ÃÄÄÄÄÄÄÄÄÄ¶             *             *             *                                                                                         ÛÛ"},
	{	"ÛÛ    ³  ÉÍ Í»  º * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *               ÛÛ"},
	{	"ÛÛ  þ ³    ®    º             *             *             *                                                                                         ÛÛ"},
	{	"ÛÛ    ³  ÈÍ Í¼  º             *             *             *                                                                                         ÛÛ"},
	{	"ÛÛ    ÃÄÄÄÄÄÄÄÄÄ¶             *             *             *                                                                                         ÛÛ"},
	{	"ÛÛ    Ï         º * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *               ÛÛ"},
	{	"ÛÛÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼                                                                                                                                   ÛÛ"},
	{	"ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ"},
	{	"ÛÛ                                                                                                                                                  ÛÛ"},
	{	"ÛÛ    ÉÍÍÍÍÍÍÍÍ»   ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿                         ÉÍÍÍÍÍÍÍÍ»   ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿                  ÛÛ"},
	{	"ÛÛ       SHIP      ³                                                  |       WAVES                TIME      ³                   |                  ÛÛ"},
	{	"ÛÛ    ÈÍÍÍÍÍÍÍÍ¼   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ      ÉÍ   Í»            ÈÍÍÍÍÍÍÍÍ¼   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ                  ÛÛ"},
	{	"ÛÛ                                                                              /3                                                                  ÛÛ"},
	{	"ÛÛ                                                                           ÈÍ   Í¼                       ÚÄÄÄÄÄÄSTOREÄÄÄÄÄÄ¿                      ÛÛ"},
	{	"ÛÛ                                                                                                  ÉÍ Í»  ³                 ³  ÉÍ Í»               ÛÛ"},
	{	"ÛÛ    ÉÍÍÍÍÍÍÍÍ»   ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿              ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿         ®    ³                 ³    ¯                 ÛÛ"},
	{	"ÛÛ     CRYSTALS    ³              |              ³                                          |       ÈÍ Í¼  ³                 ³  ÈÍ Í¼               ÛÛ"},
	{	"ÛÛ    ÈÍÍÍÍÍÍÍÍ¼   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ              ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ              ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ                      ÛÛ"},
	{	"ÛÛ                                                                                                                                                  ÛÛ"},
	{	"ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ"}
	};

	/* print out the level map array */
	int i = 0, j = 0, h = 0;
	for (j = 0; j < 41; ++j)
		for (i = 0; i < 151; ++i)
			WindowsHelper_DrawCharacterInPosition(0x0F, UI[j][i], i, j);

	/* Change colour of the ship health bar depending on the ship's health status (percentage) */
	if (shipHealth >= (SHIP_MAX_HEALTH * 0.75f))
		shipHealthColour = GREEN;
	else if ((shipHealth < (SHIP_MAX_HEALTH * 0.75f)) && (shipHealth > (SHIP_MAX_HEALTH * 0.25f)))
		shipHealthColour = YELLOW;
	else
		shipHealthColour = RED;

	/* Print the ship health. */
	i = 20;
	for (j = 0; j < shipHealth; j += 4, i++)
		WindowsHelper_DrawCharacterInPosition(shipHealthColour, (unsigned char)'Û', i, 31); 

	/* line 132 to 148: calculate the resources for printing onto the screen */
	j = resources;
	do {
		h++;
		j /= 10;
	} while (j > 0);

	i = 22 + (h / 2);
	h = 0;
	j = resources;

	do {
		h = j % 10;
		WindowsHelper_DrawCharacterInPosition(0x0F, ConvertNumToChar(h), i, 37);
		j /= 10;
		i--;
	} while (j > 0);

	WindowsHelper_DrawCharacterInPosition(0x0F, ConvertNumToChar(waveNum), 79, 33); /* Print the wave number. */
	WindowsHelper_DrawCharacterInPosition(0x0F, ConvertNumToChar(minutes), 117, 31); /* Print the timer minutes.*/
	WindowsHelper_DrawCharacterInPosition(0x0F, ':', 118, 31); /* Print the divider between minutes and seconds.*/
	WindowsHelper_DrawCharacterInPosition(0x0F, ConvertNumToChar(seconds), 119, 31); /* Print the timer seconds (first digit). */
	WindowsHelper_DrawCharacterInPosition(0x0F, ConvertNumToChar(miniSeconds), 120, 31); /* Print the timer seconds (second digit). */


	/* Store/Powerup-related UI updating */
	theTimer = timer;

	/* Render powerup icons within shop window and display store messages */
	RenderStoreUI(&timer, &store_msg_disp_start, &store_msg);
}

void Render_Starting_Tutorial(void)
{
	char UI1[][151] = { {
		"ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ" },
	{	"ÛÛ                                                                                                                                                  ÛÛ"},
	{	"ÛÛ     Greetings, Space Ranger.                                                                                                                     ÛÛ"},
	{	"ÛÛ                                                                                                                                                  ÛÛ"},
	{	"ÛÛ     Sorry to be the bearer of bad news but a horde of aliens are on their way to invade your spaceship.                                          ÛÛ"},
	{	"ÛÛ     In case you forgot the drill, here are the instructions on how to survive the alien invasion.                                                ÛÛ"},
	{	"ÛÛ                                                                                                                                                  ÛÛ"},
	{	"ÛÛ                                                                                                                                                  ÛÛ"},
	{	"ÛÛ     ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ     ÛÛ"},
	{	"ÛÛ     ÛÛ                                                                  ÛÛ                                                                ÛÛ     ÛÛ"},
	{	"ÛÛ     ÛÛ                                                        MOVE UP   ÛÛ   UP ARROW                                                     ÛÛ     ÛÛ"},
	{	"ÛÛ     ÛÛ                                                                  ÛÛ                                                                ÛÛ     ÛÛ"},
	{	"ÛÛ     ÛÛ                                                      MOVE DOWN   ÛÛ   DOWN ARROW                                                   ÛÛ     ÛÛ"},
	{	"ÛÛ     ÛÛ                                                                  ÛÛ                                                                ÛÛ     ÛÛ"},
	{	"ÛÛ     ÛÛ                                                          SHOOT   ÛÛ   SPACE BAR                                                    ÛÛ     ÛÛ"},
	{	"ÛÛ     ÛÛ                                                                  ÛÛ                                                                ÛÛ     ÛÛ"},
	{	"ÛÛ     ÛÛ                                           BROWSE THROUGH STORE   ÛÛ   LEFT & RIGHT ARROW                                           ÛÛ     ÛÛ"},
	{	"ÛÛ     ÛÛ                                                                  ÛÛ                                                                ÛÛ     ÛÛ"},
	{	"ÛÛ     ÛÛ                                            PURCHASE STORE ITEM   ÛÛ   B                                                            ÛÛ     ÛÛ"},
	{	"ÛÛ     ÛÛ                                                                  ÛÛ                                                                ÛÛ     ÛÛ"},
	{	"ÛÛ     ÛÛ                                                   INSTRUCTIONS   ÛÛ   TAB                                                          ÛÛ     ÛÛ"},
	{	"ÛÛ     ÛÛ                                                                  ÛÛ                                                                ÛÛ     ÛÛ"},
	{	"ÛÛ     ÛÛ                                                           QUIT   ÛÛ   ESC                                                          ÛÛ     ÛÛ"},
	{	"ÛÛ     ÛÛ                                                                  ÛÛ                                                                ÛÛ     ÛÛ"},
	{	"ÛÛ     ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ     ÛÛ"},
	{	"ÛÛ     ÛÛ                                                                                                                                    ÛÛ     ÛÛ"},
	{	"ÛÛ     ÛÛ                                                         ALIEN SPECIES GUIDE                                                        ÛÛ     ÛÛ"},
	{	"ÛÛ     ÛÛ                                                                                                                                    ÛÛ     ÛÛ"},
	{	"ÛÛ     ÛÛ                                 ÛÛ                               ÛÛ                                ÛÛ                              ÛÛ     ÛÛ"},
	{	"ÛÛ     ÛÛ                                 ÛÛ                               ÛÛ                                ÛÛ                              ÛÛ     ÛÛ"},
	{	"ÛÛ     ÛÛ                                 ÛÛ                               ÛÛ                                ÛÛ                              ÛÛ     ÛÛ"},
	{	"ÛÛ     ÛÛ                                 ÛÛ                               ÛÛ                                ÛÛ                              ÛÛ     ÛÛ"},
	{	"ÛÛ     ÛÛ                                 ÛÛ                               ÛÛ                                ÛÛ                              ÛÛ     ÛÛ"},
	{	"ÛÛ     ÛÛ             ABILITY:            ÛÛ            ABILITY:           ÛÛ            ABILITY:            ÛÛ           ABILITY:           ÛÛ     ÛÛ"},
	{	"ÛÛ     ÛÛ               NONE              ÛÛ          SELF-HEALING         ÛÛ         TELEPORTATION          ÛÛ        CHARGE FORWARD        ÛÛ     ÛÛ"},
	{	"ÛÛ     ÛÛ                                                                                                                                    ÛÛ     ÛÛ"},
	{	"ÛÛ     ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ     ÛÛ"},
	{	"ÛÛ                                                                                                                                                  ÛÛ"},
	{	"ÛÛ                                                                                                                    Press 'SPACE' to start...     ÛÛ"},
	{	"ÛÛ                                                                                                                                                  ÛÛ"},
	{	"ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ"}
	};

	/* Print the tutorial screen as a whole. */
	int i = 0, j = 0;
	for (j = 0; j < 41; ++j)
		for (i = 0; i < 151; ++i)
			WindowsHelper_DrawCharacterInPosition(0x0F, UI1[j][i], i, j);

	int enemyYPos = 29;

	/* Line 233 to 258: Prints the enemy figures respectively in their own colours */
	WindowsHelper_DrawCharacterInPosition(RED, (unsigned char)'‘', 26, enemyYPos + 1);
	WindowsHelper_DrawCharacterInPosition(RED, (unsigned char)'û', 25, enemyYPos + 2);
	WindowsHelper_DrawCharacterInPosition(RED, (unsigned char)'è', 26, enemyYPos + 2);
	WindowsHelper_DrawCharacterInPosition(RED, (unsigned char)'û', 27, enemyYPos + 2);
	WindowsHelper_DrawCharacterInPosition(RED, (unsigned char)'’', 26, enemyYPos + 3);

	WindowsHelper_DrawCharacterInPosition(YELLOW, (unsigned char)'”', 59, enemyYPos + 1);
	WindowsHelper_DrawCharacterInPosition(YELLOW, (unsigned char)'®', 58, enemyYPos + 2);
	WindowsHelper_DrawCharacterInPosition(YELLOW, (unsigned char)'™', 59, enemyYPos + 2);
	WindowsHelper_DrawCharacterInPosition(YELLOW, (unsigned char)'¯', 60, enemyYPos + 2);
	WindowsHelper_DrawCharacterInPosition(YELLOW, (unsigned char)'V', 59, enemyYPos + 3);

	WindowsHelper_DrawCharacterInPosition(YELLOW, (unsigned char)'ï', 92, enemyYPos + 1);
	WindowsHelper_DrawCharacterInPosition(YELLOW, (unsigned char)'À', 91, enemyYPos + 2);
	WindowsHelper_DrawCharacterInPosition(YELLOW, (unsigned char)'Ž', 92, enemyYPos + 2);
	WindowsHelper_DrawCharacterInPosition(YELLOW, (unsigned char)'Ù', 93, enemyYPos + 2);

	WindowsHelper_DrawCharacterInPosition(PURPLE, (unsigned char)'ª', 124, enemyYPos + 1);
	WindowsHelper_DrawCharacterInPosition(PURPLE, (unsigned char)'à', 125, enemyYPos + 1);
	WindowsHelper_DrawCharacterInPosition(PURPLE, (unsigned char)'©', 126, enemyYPos + 1);
	WindowsHelper_DrawCharacterInPosition(PURPLE, (unsigned char)'Ó', 124, enemyYPos + 2);
	WindowsHelper_DrawCharacterInPosition(PURPLE, (unsigned char)'×', 125, enemyYPos + 2);
	WindowsHelper_DrawCharacterInPosition(PURPLE, (unsigned char)'½', 126, enemyYPos + 2);
	WindowsHelper_DrawCharacterInPosition(PURPLE, (unsigned char)'ß', 124, enemyYPos + 3);
	WindowsHelper_DrawCharacterInPosition(PURPLE, (unsigned char)'Ð', 125, enemyYPos + 3);
	WindowsHelper_DrawCharacterInPosition(PURPLE, (unsigned char)'ß', 126, enemyYPos + 3);
}

/* Display the wave time and rest time messages */
void Render_Flow_Messages(int waveNum, bool isRestTime)
{
	int i = 0, j = 0; /* counters for the for loop for printing */
	int posX = 17, posY = 11; /* position of where the printing should start */

	char wave1[][116] = 
	{
		{ "                           ÜÛ     ÛÜ     ÜÛÛÛÛÛÛÛÛ  ÜÛ    ÛÜ     ÜÛÛÛÛÛÛÛÛ       ÜÛÛÛÛ                             "},
		{ "                          ÛÛÛ     ÛÛÛ   ÛÛÛ    ÛÛÛ ÛÛÛ    ÛÛÛ   ÛÛÛ    ÛÛÛ         ÛÛÛ                             "},
		{ "                          ÛÛÛ     ÛÛÛ   ÛÛÛ    ÛÛÛ ÛÛÛ    ÛÛÛ   ÛÛÛ    Ûß          ÛÛÛ                             "},
		{ "                          ÛÛÛ     ÛÛÛ   ÛÛÛ    ÛÛÛ ÛÛÛ    ÛÛÛ  ÜÛÛÛÜÜÜ             ÛÛÛ                             "},
		{ "                          ÛÛÛ     ÛÛÛ ßÛÛÛÛÛÛÛÛÛÛÛ ÛÛÛ    ÛÛÛ ßßÛÛÛßßß             ÛÛÛ                             "},
		{ "                          ÛÛÛ     ÛÛÛ   ÛÛÛ    ÛÛÛ ÛÛÛ    ÛÛÛ   ÛÛÛ    ÛÜ          ÛÛÛ                             "},
		{ "                          ÛÛÛ ÜÛÜ ÛÛÛ   ÛÛÛ    ÛÛÛ ÛÛÛ    ÛÛÛ   ÛÛÛ    ÛÛÛ         ÛÛÛ                             "},
		{ "                           ßÛÛÛßÛÛÛß    ÛÛÛ    Ûß   ßÛÛÛÛÛÛß    ÛÛÛÛÛÛÛÛÛÛ      ÜÛÛÛÛÛÛÛß                          "},
		{ "                                                                                                                   "},
		{ "                                         THE ALIENS ARE COMING... GET READY!                                       "},
		{ "                              THERE ARE THINGS IN THE STORE THAT CAN AID IN YOUR BATTLE                            "},

	};

	char wave2[][116] = 
	{
		{ "                         ÜÛ     ÛÜ     ÜÛÛÛÛÛÛÛÛ  ÜÛ    ÛÜ     ÜÛÛÛÛÛÛÛÛ       ÜÛÛÛÛÛÛÛÛÛÛ                         "},
		{ "                        ÛÛÛ     ÛÛÛ   ÛÛÛ    ÛÛÛ ÛÛÛ    ÛÛÛ   ÛÛÛ    ÛÛÛ               ÛÛÛ                         "},
		{ "                        ÛÛÛ     ÛÛÛ   ÛÛÛ    ÛÛÛ ÛÛÛ    ÛÛÛ   ÛÛÛ    Ûß                ÛÛÛ                         "},
		{ "                        ÛÛÛ     ÛÛÛ   ÛÛÛ    ÛÛÛ ÛÛÛ    ÛÛÛ  ÜÛÛÛÜÜÜ           ÜÛÛÛÛÛÛÛÛÛß                         "},
		{ "                        ÛÛÛ     ÛÛÛ ßÛÛÛÛÛÛÛÛÛÛÛ ÛÛÛ    ÛÛÛ ßßÛÛÛßßß          ÛÛÛß                                 "},
		{ "                        ÛÛÛ     ÛÛÛ   ÛÛÛ    ÛÛÛ ÛÛÛ    ÛÛÛ   ÛÛÛ    ÛÜ       ÛÛÛ                                  "},
		{ "                        ÛÛÛ ÜÛÜ ÛÛÛ   ÛÛÛ    ÛÛÛ ÛÛÛ    ÛÛÛ   ÛÛÛ    ÛÛÛ      ÛÛÛ                                  "},
		{ "                         ßÛÛÛßÛÛÛß    ÛÛÛ    Ûß   ßÛÛÛÛÛÛß    ÛÛÛÛÛÛÛÛÛÛ      ÛÛÛÛÛÛÛÛÛÛÛß                         "},
		{ "                                                                                                                   "},
		{ "                             SEEMS LIKE A NEW ALIEN KIND HAS ARRIVED... BRACE YOURSELF!                            "},
		{ "                               NEW UPGRADES AND POWER-UPS ARE AVAILABLE IN THE STORE                               "}
	};

	char wave3[][116] = 
	{
		{ "                         ÜÛ     ÛÜ     ÜÛÛÛÛÛÛÛÛ  ÜÛ    ÛÜ     ÜÛÛÛÛÛÛÛÛ       ÜÛÛÛÛÛÛÛÛÛÜ                         "},
		{ "                        ÛÛÛ     ÛÛÛ   ÛÛÛ    ÛÛÛ ÛÛÛ    ÛÛÛ   ÛÛÛ    ÛÛÛ               ÛÛÛ                         "},
		{ "                        ÛÛÛ     ÛÛÛ   ÛÛÛ    ÛÛÛ ÛÛÛ    ÛÛÛ   ÛÛÛ    Ûß                ÛÛÛ                         "},
		{ "                        ÛÛÛ     ÛÛÛ   ÛÛÛ    ÛÛÛ ÛÛÛ    ÛÛÛ  ÜÛÛÛÜÜÜ            ÜÜÜÜÜÜÜÛÛÛ                         "},
		{ "                        ÛÛÛ     ÛÛÛ ßÛÛÛÛÛÛÛÛÛÛÛ ÛÛÛ    ÛÛÛ ßßÛÛÛßßß            ßßßßßßßÛÛÛ                         "},
		{ "                        ÛÛÛ     ÛÛÛ   ÛÛÛ    ÛÛÛ ÛÛÛ    ÛÛÛ   ÛÛÛ    ÛÜ                ÛÛÛ                         "},
		{ "                        ÛÛÛ ÜÛÜ ÛÛÛ   ÛÛÛ    ÛÛÛ ÛÛÛ    ÛÛÛ   ÛÛÛ    ÛÛÛ               ÛÛÛ                         "},
		{ "                         ßÛÛÛßÛÛÛß    ÛÛÛ    Ûß   ßÛÛÛÛÛÛß    ÛÛÛÛÛÛÛÛÛÛ       ÜÛÛÛÛÛÛÛÛÛß                         "},
		{ "                                                                                                                   "},
		{ "                                      THE TOUGHEST SPECIES ARE HERE... GODSPEED!                                   "},
		{ "                               NEW UPGRADES AND POWER-UPS ARE AVAILABLE IN THE STORE                               "}
	};

	char waveOver[][116] = 
	{
		{ "        ÜÛ     ÛÜ     ÜÛÛÛÛÛÛÛÛ  ÜÛ    ÛÜ     ÜÛÛÛÛÛÛÛÛ       ÜÛÛÛÛÛÛÜ   ÜÛ    ÛÜ     ÜÛÛÛÛÛÛÛÛ    ÜÛÛÛÛÛÛÛÛ       "},
		{ "       ÛÛÛ     ÛÛÛ   ÛÛÛ    ÛÛÛ ÛÛÛ    ÛÛÛ   ÛÛÛ    ÛÛÛ      ÛÛÛ    ÛÛÛ ÛÛÛ    ÛÛÛ   ÛÛÛ    ÛÛÛ   ÛÛÛ    ÛÛÛ       "},
		{ "       ÛÛÛ     ÛÛÛ   ÛÛÛ    ÛÛÛ ÛÛÛ    ÛÛÛ   ÛÛÛ    Ûß       ÛÛÛ    ÛÛÛ ÛÛÛ    ÛÛÛ   ÛÛÛ    Ûß    ÛÛÛ    ÛÛÛ       "},
		{ "       ÛÛÛ     ÛÛÛ   ÛÛÛ    ÛÛÛ ÛÛÛ    ÛÛÛ  ÜÛÛÛÜÜÜ          ÛÛÛ    ÛÛÛ ÛÛÛ    ÛÛÛ  ÜÛÛÛÜÜÜ      ÜÛÛÛÜÜÜÜÛÛß       "},
		{ "       ÛÛÛ     ÛÛÛ ßÛÛÛÛÛÛÛÛÛÛÛ ÛÛÛ    ÛÛÛ ßßÛÛÛßßß          ÛÛÛ    ÛÛÛ ÛÛÛ    ÛÛÛ ßßÛÛÛßßß     ßßÛÛÛßßßßß         "},
		{ "       ÛÛÛ     ÛÛÛ   ÛÛÛ    ÛÛÛ ÛÛÛ    ÛÛÛ   ÛÛÛ    ÛÜ       ÛÛÛ    ÛÛÛ ÛÛÛ    ÛÛÛ   ÛÛÛ    ÛÜ  ßÛÛÛÛÛÛÛÛÛÛÛ       "},
		{ "       ÛÛÛ ÜÛÜ ÛÛÛ   ÛÛÛ    ÛÛÛ ÛÛÛ    ÛÛÛ   ÛÛÛ    ÛÛÛ      ÛÛÛ    ÛÛÛ ÛÛÛ    ÛÛÛ   ÛÛÛ    ÛÛÛ   ÛÛÛ    ÛÛÛ       "},
		{ "        ßÛÛÛßÛÛÛß    ÛÛÛ    Ûß   ßÛÛÛÛÛÛß    ÛÛÛÛÛÛÛÛÛÛ       ßÛÛÛÛÛÛß   ßÛÛÛÛÛÛß    ÛÛÛÛÛÛÛÛÛÛ   ÛÛÛ    ÛÛÛ       "},
		{ "                                                                                                                   "},
		{ "                                           GOOD JOB IN SURVIVING THE WAVE!                                         "},
		{ "                              YOU CAN TAKE A BREATHER AND PLAN AHEAD FOR THE NEXT WAVE                             "}
	};

	/* if it is not rest time */
	if (isRestTime == false)
	{
		/* prints the starting wave message respectively */
		if (waveNum == 1)
		{
			posX = 17;
			posY = 11;
			for (j = 0; j < 11; ++j, ++posY)
			{
				for (i = 0; i < 116; ++i, ++posX)
				{
					WindowsHelper_DrawCharacterInPosition(0x0F, wave1[j][i], posX, posY);
				}

				posX = 17;
			}
		}

		if (waveNum == 2)
		{
			posX = 17;
			posY = 11;
			for (j = 0; j < 11; ++j, ++posY)
			{
				for (i = 0; i < 116; ++i, ++posX)
				{
					WindowsHelper_DrawCharacterInPosition(0x0F, wave2[j][i], posX, posY);
				}

				posX = 17;
			}
		}

		if (waveNum == 3)
		{
			posX = 17;
			posY = 11;
			for (j = 0; j < 11; ++j, ++posY)
			{
				for (i = 0; i < 116; ++i, ++posX)
				{
					WindowsHelper_DrawCharacterInPosition(0x0F, wave3[j][i], posX, posY);
				}

				posX = 17;
			}
		}
	}
	else /* if it is rest time, print the rest time message */
	{
		posX = 17;
		posY = 11;
		for (j = 0; j < 11; ++j, ++posY)
		{
			for (i = 0; i < 116; ++i, ++posX)
			{
				WindowsHelper_DrawCharacterInPosition(0x0F, waveOver[j][i], posX, posY);
			}

			posX = 17;
		}
	}
}

/* Display store-related messages like when the player buys something */
void DisplayStoreMessage(char string[])
{
	int i;

	store_msg_disp_start = theTimer;

	/* Wipe the message at first */
	ResetStoreMsg();

	for (i = 0; i < (int)strlen(string); i++)
		store_msg[i] = string[i];
}

/* Wipe the contents of the store message string */
void ResetStoreMsg(void)
{
	int i;

	for (i = 0; i < (sizeof(store_msg) / sizeof(store_msg[0])); i++)
		store_msg[i] = '\0';
}