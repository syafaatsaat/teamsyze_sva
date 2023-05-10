/***********************************************************************************
All content © 2018 DigiPen Institute of Technology Singapore, all rights reserved.

Filename    Player.c
Author      Chua Zun Sheng
DP email    zunsheng.chua@digipen.edu
Course      GAM100

Brief Description:
	The functions of player.c
***********************************************************************************/
#include <stdio.h>
#include <Windows.h>
#include "WindowsHelper.h"
#include "Projectiles.h"
#include "Player.h"
#include "Game.h"
#include "Player.h"
#include "Store.h"
#include "GameStateLevel1.h"
#include "Weapon.h"
#include "Tower.h"
#include "Powerups.h"

Player player;
enum Colour playerColour;
float nextColourChangeTime;

/* Input detection/handling for various keys */
bool upKey_PressedOnce;
bool upKey_PreviouslyDown;
bool downKey_PressedOnce;
bool downKey_PreviouslyDown;
bool spaceKey_PressedOnce;
bool spaceKey_PreviouslyDown;
bool spaceKey_Pressed;
bool rKey_PressedOnce;
bool rKey_PreviouslyDown;
bool escKey_PressedOnce;
bool escKey_PreviouslyDown;
bool leftKey_PressedOnce;
bool leftKey_PreviouslyDown;
bool rightKey_PressedOnce;
bool rightKey_PreviouslyDown;
bool bKey_PressedOnce;
bool bKey_PreviouslyDown;
bool enterKeyG_PressedOnce;
bool enterKeyG_PreviouslyDown;
bool tabKey_PressedOnce;
bool tabKey_PreviouslyDown;

/*******************************************************************************
Function: Player_Init
Description: initialise the player status
*******************************************************************************/
void Player_Init(void) {
	player.Pos_X = 36;
	player.Pos_Y = 3;

	playerColour = GREEN;

	playerTile = 0;

	InitWeapon();
	InitPowerups();
	InitStore();
	removeTowers();

	upKey_PressedOnce = false;
	upKey_PreviouslyDown = false;
	downKey_PressedOnce = false;
	downKey_PreviouslyDown = false;
	spaceKey_PressedOnce = false;
	spaceKey_PreviouslyDown = false;
	spaceKey_Pressed = false;
	rKey_PressedOnce = false;
	rKey_PreviouslyDown = false;
	escKey_PressedOnce = false;
	escKey_PreviouslyDown = false;
	leftKey_PressedOnce = false;
	leftKey_PreviouslyDown = false;
	rightKey_PressedOnce = false;
	rightKey_PreviouslyDown = false;
	bKey_PressedOnce = false;
	bKey_PreviouslyDown = false;
	enterKeyG_PressedOnce = false;
	enterKeyG_PreviouslyDown = false;
	tabKey_PressedOnce = false;
	tabKey_PreviouslyDown = false;

	for (int i = 0; i < PLAYER_BULLET; ++i) {
		Player_Bullet[i].shoot = false;
		Player_Bullet[i].Pos_X = player.Pos_X;
		Player_Bullet[i].Pos_Y = player.Pos_Y;
		Player_Bullet[i].id = i + 1;
		Player_Bullet[i].fromPlayer = true;
	}
}


/*******************************************************************************
Function: UpdatePlayerKeyboardInput
Description: Keyboard input for the player
*******************************************************************************/
void UpdatePlayerKeyboardInput(void)
{
	if (!retGame_Paused())
	{
		if (GetAsyncKeyState(VK_LEFT) < 0)
		{
			if (!leftKey_PreviouslyDown)
			{
				leftKey_PressedOnce = true;

				leftKey_PreviouslyDown = true;
			}
			else
				leftKey_PressedOnce = false;
		}
		else
			leftKey_PreviouslyDown = false;

		if (GetAsyncKeyState(VK_RIGHT) < 0)
		{
			if (!rightKey_PreviouslyDown)
			{
				rightKey_PressedOnce = true;

				rightKey_PreviouslyDown = true;
			}
			else
				rightKey_PressedOnce = false;
		}
		else
			rightKey_PreviouslyDown = false;

		if (GetAsyncKeyState(VK_SPACE) < 0)
			spaceKey_Pressed = true;
		else
			spaceKey_Pressed = false;

		if (spaceKey_Pressed)
		{
			if (!spaceKey_PreviouslyDown)
			{
				spaceKey_PressedOnce = true;

				spaceKey_PreviouslyDown = true;
			}
			else
				spaceKey_PressedOnce = false;
		}
		else
			spaceKey_PreviouslyDown = false;

		if (GetAsyncKeyState('R') < 0)
		{
			if (!rKey_PreviouslyDown)
			{
				rKey_PressedOnce = true;

				rKey_PreviouslyDown = true;
			}
			else
				rKey_PressedOnce = false;
		}
		else
			rKey_PreviouslyDown = false;

		if (GetAsyncKeyState(VK_ESCAPE) < 0)
		{
			if (!escKey_PreviouslyDown)
			{
				escKey_PressedOnce = true;

				Game_Paused();

				escKey_PreviouslyDown = true;
			}
			else
				escKey_PressedOnce = false;
		}
		else
			escKey_PreviouslyDown = false;

		if (GetAsyncKeyState(VK_TAB) < 0)
		{
			if (!tabKey_PreviouslyDown)
			{
				tabKey_PressedOnce = true;
				Instruction_Paused();
				tabKey_PreviouslyDown = true;
			}
			else
				tabKey_PressedOnce = false;
		}
		else
			tabKey_PreviouslyDown = false;

		if (GetAsyncKeyState('b') < 0 || GetAsyncKeyState('B') < 0)
		{
			if (!bKey_PreviouslyDown)
			{
				bKey_PressedOnce = true;

				bKey_PreviouslyDown = true;
			}
			else
				bKey_PressedOnce = false;
		}
		else
			bKey_PreviouslyDown = false;
	}
	else
	{
		
	}
	
	if (GetAsyncKeyState(VK_RETURN) < 0)
	{
		if (!enterKeyG_PreviouslyDown)
		{
			enterKeyG_PressedOnce = true;

			enterKeyG_PreviouslyDown = true;
		}
		else
			enterKeyG_PressedOnce = false;
	}
	else
		enterKeyG_PreviouslyDown = false;

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
}

/*******************************************************************************
Function: Player_Update
Description: The update function of player
*******************************************************************************/
void Player_Update(float dt) 
{
	UpdatePlayerKeyboardInput();
	Projectile_Update(Player_Bullet, PLAYER_BULLET);	
	
	if (retGame_Paused())
	{
		if (upKey_PressedOnce)
			Game_QuitResume();

		if (downKey_PressedOnce)
			Game_QuitResume();

		if (enterKeyG_PressedOnce)
		{
			if (retGame_QuitResume())
			{
				Game_GameQuit();
			}
			else
			{
				Game_Unpaused();
			}
		}
	}
	else if (retInstruction_Paused())
	{
		if (enterKeyG_PressedOnce)
		{
			Instruction_Unpaused();
		}
	}
	else
	{
		if (upKey_PressedOnce) {
			if (player.Pos_Y > 4) {
				playerTile--;
				player.Pos_Y -= 4;
			}
		}
		if (downKey_PressedOnce) {
			if (player.Pos_Y < 23) {
				playerTile++;
				player.Pos_Y += 4;
			}
		}			
	}

	/* Scroll through the store */
	if (leftKey_PressedOnce)
		Store_PreviousSelection();

	if (rightKey_PressedOnce)
		Store_NextSelection();

	/* Purchase currently-selected powerup */
	if (bKey_PressedOnce)
		Store_PurchaseSelectedItem(GetResourcesPtr(), GetShipHealthPtr());

	/* Update power-up related timers */
	UpdatePowerupTimers(dt);
	
	/* Fire weapon depending on the fire-rate and auto-fire state */
	UpdateWeaponStatTimers(dt);

	if (GetPlayerWeaponAutoFireState())
	{
		if (spaceKey_Pressed)
		{
			if (GetPlayerWeaponCanFire())
			{
				for (int i = 0; i < PLAYER_BULLET; ++i)
				{
					if (Player_Bullet[i].shoot == false)
					{
						Player_Bullet[i].shoot = true;
						Player_Bullet[i].Pos_X = player.Pos_X;
						Player_Bullet[i].Pos_Y = player.Pos_Y;
						break;
					}
				}

				ResetPlayerWeaponCooldownTimer();
			}
		}
	}
	else
	{
		if (spaceKey_PressedOnce)
		{
			if (GetPlayerWeaponCanFire())
			{
				for (int i = 0; i < PLAYER_BULLET; ++i)
				{
					if (Player_Bullet[i].shoot == false)
					{
						Player_Bullet[i].shoot = true;
						Player_Bullet[i].Pos_X = player.Pos_X;
						Player_Bullet[i].Pos_Y = player.Pos_Y;
						break;
					}
				}

				ResetPlayerWeaponCooldownTimer();
			}
		}
	}	
}

/*******************************************************************************
Function: Render_Player
Description: Render the player and projectile
*******************************************************************************/
void Render_Player(void)
{
	/* Change the colour of the player depending on if insta-kill mode is activated */
	if ((GetInstaKillPowerupTimer() >= (INSTAKILL_POWERUP_DURATION / 4)) && !GetDeactivatedInstaKillPowerupState())
	{
		playerColour = RED;
		nextColourChangeTime = (INSTAKILL_POWERUP_DURATION / 4);
	}
	else if ((GetInstaKillPowerupTimer() < (INSTAKILL_POWERUP_DURATION / 4)) && !GetDeactivatedInstaKillPowerupState())
	{
		if (GetInstaKillPowerupTimer() < nextColourChangeTime)
		{
			if (playerColour == RED)
				playerColour = GREEN;
			else
				playerColour = RED;

			nextColourChangeTime = GetInstaKillPowerupTimer() - COLOUR_CHANGE_DURATION;
		}
	}
	else
		playerColour = GREEN;

	WindowsHelper_DrawCharacterInPosition(playerColour, (unsigned char)'ê', player.Pos_X + 1, player.Pos_Y);
	WindowsHelper_DrawCharacterInPosition(playerColour, (unsigned char)'œ', player.Pos_X, player.Pos_Y+1);
	WindowsHelper_DrawCharacterInPosition(playerColour, (unsigned char)'á', player.Pos_X+1, player.Pos_Y+1);
	WindowsHelper_DrawCharacterInPosition(playerColour, (unsigned char)'©', player.Pos_X+2, player.Pos_Y+1);
	WindowsHelper_DrawCharacterInPosition(playerColour, (unsigned char)'Ó', player.Pos_X + 1, player.Pos_Y+2);
	Projectile_Render(Player_Bullet, PLAYER_BULLET);
}

/*******************************************************************************
Function: Get/Set Function
Description: Get and set of the player
*******************************************************************************/
int Get_PlayerPosX(void) {
	return player.Pos_X;
}

int Get_PlayerPosY(void) {
	return player.Pos_Y;
}

void Set_PlayerPosX(int Pos_X) {
	player.Pos_X = Pos_X;
}

void Set_PlayerPosY(int Pos_Y) {
	player.Pos_Y = Pos_Y;
}

Player *Get_PlayerStruct(void)
{
	return &player;
}