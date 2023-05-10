﻿/***********************************************************************************
All content © 2018 DigiPen Institute of Technology Singapore, all rights reserved.

Filename:    GameOver.c
Author(s):   Syafaat (100%)

Description/Features:
  This file contains the printed ASCII art for the game over screen.
***********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "WindowsHelper.h"

/*Function for printing game over screen*/
void Render_GameOver(void)
{
	char UI[][151] = {
		{"ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                 The ALIENS have now taken over the earth and here comes the end of human race. :(                                ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                       ÜÛÛÛÛ  ÜÜÜ       ÛÛÛÜ ÜÛÛÛ²²ÛÛÛÛÛ     ±ÛÛÛÛÛ   ÛÛ±   Û²²ÛÛÛÛÛ  ÛÛßÛÛÛ                                      ÛÛ"},
		{"ÛÛ                                       ÛÛ± ßÛ±±ÛÛÛÛÜ    ²ÛÛ±ßÛß ÛÛ±²Û   ß    ±ÛÛ±  ÛÛ±²ÛÛ°   Û±²Û   ß ²ÛÛ ± ÛÛ±                                   ÛÛ"},
		{"ÛÛ                                      ±ÛÛ°ÜÜÜ°±ÛÛ  ßÛÜ  ²ÛÛ    ²ÛÛ°±ÛÛÛ      ±ÛÛ°  ÛÛ± ²ÛÛ  Û±°±ÛÛÛ   ²ÛÛ °ÜÛ ±                                   ÛÛ"},
		{"ÛÛ                                      °²Û  ÛÛ²°ÛÛÜÜÜÜÛÛ ±ÛÛ    ±ÛÛ ±²Û  Ü    ±ÛÛ   ÛÛ°  ±ÛÛ Û°°±²Û  Ü ±ÛÛßßÛÜ                                     ÛÛ"},
		{"ÛÛ                                      °±²ÛÛÛß± ²Û   ²ÛÛ±±ÛÛ±   °ÛÛ±°±ÛÛÛÛ±   ° ÛÛÛÛ²±°   ±ÛÛ°  °±ÛÛÛÛ±°ÛÛ² ±ÛÛ±                                   ÛÛ"},
		{"ÛÛ                                      °±   ±  ±±   ²±Û°° ±°   °  °°° ±° °   ° ±°±°±°    ° °°  °° ±° °° ±² °±²°                                    ÛÛ"},
		{"ÛÛ                                        °   °   ±   ±± °°  °      ° ° °  °     ° ± ±°    ° °°   ° °  °  °± ° ±°                                   ÛÛ"},
		{"ÛÛ                                      ° °   °   °   ±   °      °      °      ° ° ° ±       °°     °     °°   °                                    ÛÛ"},
		{"ÛÛ                                            °       °  °       °      °  °       ° °        °     °  °   °                                        ÛÛ"},
		{"ÛÛ                                                                                           °                                                      ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                PRESS ESC TO MAIN MENU                                                            ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ"}
	};

	int i, j = 0;
	for (j = 0; j < 41; ++j)
		for (i = 0; i < 151; ++i)
			WindowsHelper_DrawCharacterInPosition(0x0F, UI[j][i], i, j);
}

/*Function for printing victory screen*/
void Render_GameVictory(void)
{
	char UI[][151] = {
		{"ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ"},
		{"ÛÛ                                                                                                                                            *     ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                               *                                  *                                                               ÛÛ"},
		{"ÛÛ                                                                                                                     *                            ÛÛ"},
		{"ÛÛ        *                                                                                                                                         ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                       ÜÛ    ÛÜ   ÜÛ   ÜÛÛÛÛÛÛÛÛ     ÛÛÛ      ÜÛÛÛÛÛÛÜ     ÜÛÛÛÛÛÛÛÛ ÜÛÛ   Ü                                      ÛÛ"},
		{"ÛÛ                                      ÛÛÛ    ÛÛÛ ÛÛÛ  ÛÛÛ    ÛÛÛ ßÛÛÛÛÛÛÛÛÛÜ ÛÛÛ    ÛÛÛ   ÛÛÛ    ÛÛÛ ÛÛÛ   ÛÛÜ                                    ÛÛ"},
		{"ÛÛ                                      ÛÛÛ    ÛÛÛ ÛÛÛÝ ÛÛÛ    Ûß     ßÛÛÛßßÛÛ ÛÛÛ    ÛÛÛ   ÛÛÛ  * ÛÛÛ ÛÛÛÜÜÜÛÛÛ                                    ÛÛ"},
		{"ÛÛ                        *             ÛÛÛ    ÛÛÛ ÛÛÛÝ ÛÛÛ            ÛÛÛ   ß ÛÛÛ    ÛÛÛ  ÜÛÛÛÜÜÜÜÛÛß ßßßßßßÛÛÛ                                    ÛÛ"},
		{"ÛÛ                                      ÛÛÛ    ÛÛÛ ÛÛÛÝ ÛÛÛ       *    ÛÛÛ     ÛÛÛ    ÛÛÛ ßßÛÛÛßßßßß   ÜÛÛ   ÛÛÛ                                    ÛÛ"},
		{"ÛÛ                                      ÛÛÛ    ÛÛÛ ÛÛÛ  ÛÛÛ    ÛÜ      ÛÛÛ     ÛÛÛ    ÛÛÛ ßÛÛÛÛÛÛÛÛÛÛÛ ÛÛÛ   ÛÛÛ                                    ÛÛ"},
		{"ÛÛ                                      ÛÛÛ    ÛÛÛ ÛÛÛ  ÛÛÛ    ÛÛÛ     ÛÛÛ     ÛÛÛ    ÛÛÛ   ÛÛÛ    ÛÛÛ ÛÛÛ   ÛÛÛ                                    ÛÛ"},
		{"ÛÛ                                       ßÛÛÛÛÛÛß  Ûß   ÛÛÛÛÛÛÛÛß     ÜÛÛÛÛß    ßÛÛÛÛÛÛß    ÛÛÛ    ÛÛÛ  ßÛÛÛÛÛß                     *               ÛÛ"},
		{"ÛÛ                                                                                          ÛÛÛ    ÛÛÛ                                              ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                     *                                                                            ÛÛ"},
		{"ÛÛ                 *                                                                                                                                ÛÛ"},
		{"ÛÛ                                                               WELL DONE, SPACE RANGER!                                                           ÛÛ"},
		{"ÛÛ                                                            * THE ALIENS LOSE THIS ROUND *               *                                *       ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ  *                                                                                                                                               ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                PRESS ESC TO MAIN MENU                                                            ÛÛ"},
		{"ÛÛ                                    *                                                                                                             ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                                               *                                                  ÛÛ"},
		{"ÛÛ                                                                                                                        *          *              ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                *                                   *                                                                                             ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                      *                                                                       *                                                   ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                                                                                                  ÛÛ"},
		{"ÛÛ                                                                                                                                          *       ÛÛ"},
		{"ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ"}
	};

	int i, j = 0;
	for (j = 0; j < 41; ++j)
		for (i = 0; i < 151; ++i)
			WindowsHelper_DrawCharacterInPosition(0x0F, UI[j][i], i, j);
}