/***********************************************************************************
All content © 2018 DigiPen Institute of Technology Singapore, all rights reserved.

Filename    Tower.c
Author      Chua Zun Sheng
DP email    zunsheng.chua@digipen.edu
Course      GAM100

Brief Description:
	The functions of Tower.c
***********************************************************************************/
#include "Tower.h"

/*******************************************************************************
Function: towerUpdate
Description: Update the tower status, eg shooting/constructing
*******************************************************************************/
void towerUpdate(float dt) {
	for (int i = 0; i < NumOfTurret; ++i) {
		if (turrets[i].enable == true) {
			Projectile_Update(turrets[i].turretBullet,1);
			turrets[i].timer += dt;
			if (turrets[i].timer > TurretFireRate) {
				turrets[i].shoot = true;
				turrets[i].timer = 0;
			}
			if (turrets[i].shoot == true) {
				if (turrets[i].turretBullet[0].shoot == false){
						turrets[i].turretBullet[0].Pos_X = turrets[i].Pos_X;
						turrets[i].turretBullet[0].Pos_Y = turrets[i].Pos_Y;
						turrets[i].turretBullet[0].shoot = true;
				}
				turrets[i].shoot = false;
			}
		}
	}

	for (int i = 0; i < NumOfWall; ++i) {
		if (walls[i].enable == true) {
			if (walls[i].health < 0)
				walls[i].enable = false;
		}
	}
}

/*******************************************************************************
Function: renderTower
Description: render the tower, eg wall or turret
*******************************************************************************/
void renderTower(void) {
	int i;
	for (i = 0; i < NumOfTurret; ++i) {
		if (turrets[i].enable == true) {
			WindowsHelper_DrawCharacterInPosition(0x0f, (unsigned char)'Û', turrets[i].Pos_X, turrets[i].Pos_Y);
			WindowsHelper_DrawCharacterInPosition(0x0f, (unsigned char)'©', turrets[i].Pos_X, turrets[i].Pos_Y + 1);
			WindowsHelper_DrawCharacterInPosition(0x0f, (unsigned char)'Û', turrets[i].Pos_X, turrets[i].Pos_Y + 2);
			WindowsHelper_DrawCharacterInPosition(0x0f, (unsigned char)'Û', turrets[i].Pos_X - 1, turrets[i].Pos_Y);
			WindowsHelper_DrawCharacterInPosition(0x0f, (unsigned char)'Û', turrets[i].Pos_X - 1, turrets[i].Pos_Y + 1);
			WindowsHelper_DrawCharacterInPosition(0x0f, (unsigned char)'Û', turrets[i].Pos_X - 1, turrets[i].Pos_Y + 2);
			WindowsHelper_DrawCharacterInPosition(0x0f, (unsigned char)'Û', turrets[i].Pos_X - 2, turrets[i].Pos_Y);
			WindowsHelper_DrawCharacterInPosition(0x0f, (unsigned char)'Û', turrets[i].Pos_X - 2, turrets[i].Pos_Y + 1);
			WindowsHelper_DrawCharacterInPosition(0x0f, (unsigned char)'Û', turrets[i].Pos_X - 2, turrets[i].Pos_Y + 2);
			Projectile_Render(turrets[i].turretBullet,1);
		}
	}
	for (i = 0; i < NumOfWall; ++i) {
		if (walls[i].enable == true)
		{
			WindowsHelper_DrawCharacterInPosition(0x0f, (unsigned char)'Û', walls[i].Pos_X, walls[i].Pos_Y);
			WindowsHelper_DrawCharacterInPosition(0x0f, (unsigned char)'Û', walls[i].Pos_X, walls[i].Pos_Y + 1);
			WindowsHelper_DrawCharacterInPosition(0x0f, (unsigned char)'Û', walls[i].Pos_X, walls[i].Pos_Y + 2);
			WindowsHelper_DrawCharacterInPosition(0x0f, (unsigned char)'Û', walls[i].Pos_X - 1, walls[i].Pos_Y);
			WindowsHelper_DrawCharacterInPosition(0x0f, (unsigned char)'Û', walls[i].Pos_X - 1, walls[i].Pos_Y + 1);
			WindowsHelper_DrawCharacterInPosition(0x0f, (unsigned char)'Û', walls[i].Pos_X - 1, walls[i].Pos_Y + 2);
		}
	}
}

/*******************************************************************************
Function: buildTurret
Description: Building a turret
*******************************************************************************/
void buildTurret(void) {
	if (turrets[playerTile].enable == false) {
		turrets[playerTile].enable = true;
		turrets[playerTile].Pos_X = Get_PlayerPosX() - 12;
		turrets[playerTile].Pos_Y = Get_PlayerPosY();
	}
}

/*******************************************************************************
Function: buildWal
Description: Building a wall
*******************************************************************************/
void buildWall(void) {
	if (walls[playerTile].enable == false) {
		walls[playerTile].enable = true;
		walls[playerTile].health = WallHealth;
		walls[playerTile].Pos_X = Get_PlayerPosX() + 15;
		walls[playerTile].Pos_Y = Get_PlayerPosY();
	}
}

/*******************************************************************************
Function: removeTowers
Description: Remove all the tower on the screen
*******************************************************************************/
void removeTowers(void) {
	for (int i = 0; i < NumOfWall; ++i) {
		walls[i].enable = false;
		turrets[i].enable = false;
	}
}