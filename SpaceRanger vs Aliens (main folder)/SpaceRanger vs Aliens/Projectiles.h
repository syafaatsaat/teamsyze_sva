/***********************************************************************************
All content © 2018 DigiPen Institute of Technology Singapore, all rights reserved.

Filename    Projectiles.h
Author      Chua Zun Sheng
DP email    zunsheng.chua@digipen.edu
Course      GAM100

Brief Description:
	The struct and function prototype of the projectile 
***********************************************************************************/
#pragma once
#include <stdbool.h>

#define PLAYER_BULLET 30

typedef struct Projectiles {
	int Pos_X;
	int Pos_Y;
	int id;
	bool shoot;
	bool render;
	bool fromPlayer;
} Projectile;

void Projectile_Update(Projectile projectiles[], int bulletCount);
void Projectile_Render(Projectile projectiles[], int bulletCount);
int GetNumActivePlayerProjectiles(void);

