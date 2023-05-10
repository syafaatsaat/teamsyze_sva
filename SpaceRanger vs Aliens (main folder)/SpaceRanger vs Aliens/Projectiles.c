/***********************************************************************************
All content © 2018 DigiPen Institute of Technology Singapore, all rights reserved.

Filename    Projectiles.c
Author      Chua Zun Sheng
DP email    zunsheng.chua@digipen.edu
Course      GAM100

Brief Description:
	The functions of Projectiles.c
***********************************************************************************/
#include <stdio.h>
#include "WindowsHelper.h"
#include "Player.h"
#include "Projectiles.h"
#include "Weapon.h"

int num_active_player_projectiles;

/*******************************************************************************
Function: Projectile_Update
Description: Update the position of the projectile
*******************************************************************************/
void Projectile_Update( Projectile projectiles[], int bulletCount) {

	num_active_player_projectiles = 0;

	int i;
	for (i = 0; i < bulletCount; ++i) {
		if (projectiles[i].shoot == true) {
			projectiles[i].Pos_X += 1;
   			if (projectiles[i].Pos_X > WindowsHelper_GetConsoleWidth())
				projectiles[i].shoot = false;

			if (projectiles[i].fromPlayer)
				num_active_player_projectiles++;
		}
	}
}

/*******************************************************************************
Function: Projectile_Render
Description: Render the projectile
*******************************************************************************/
void Projectile_Render(Projectile projectiles[], int bulletCount) {
	int i;
	for (i = 0; i < bulletCount; ++i) {
		if (projectiles[i].shoot == true) {
			/* Render standard projectile if player fires non-piercing projectiles, or if it is fired from a turret */
			if (!GetPlayerWeaponPiercingShotsState() || !projectiles[i].fromPlayer)
				WindowsHelper_DrawCharacterInPosition(WHITE, '-', projectiles[i].Pos_X, projectiles[i].Pos_Y + 1);
			/*Render piercing projectile */
			else
				WindowsHelper_DrawCharacterInPosition(WHITE, '>', projectiles[i].Pos_X, projectiles[i].Pos_Y + 1);
		}
	}
}

/*******************************************************************************
Function: GetNumActivePlayerProjectiles
Description: Return the number of active player projectile
*******************************************************************************/
int GetNumActivePlayerProjectiles(void)
{
	return num_active_player_projectiles;
}