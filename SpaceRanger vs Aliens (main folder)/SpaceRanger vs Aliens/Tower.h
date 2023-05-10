/***********************************************************************************
All content © 2018 DigiPen Institute of Technology Singapore, all rights reserved.

Filename    tower.h
Author      Chua Zun Sheng
DP email    zunsheng.chua@digipen.edu
Course      GAM100

Brief Description:
	The struct and functions prototype of tower.h
***********************************************************************************/
#pragma once
#include "Projectiles.h"
#include "Includes.h"
#include "Player.h"
#include "WindowsHelper.h"

#define TurretFireRate 10
#define NumOfTurret 6
#define NumOfWall 6
#define TurretDmg 15
#define WallHealth 300


typedef struct turret_s {
	int enable;
	int Pos_X;
	int Pos_Y;
	float timer;
	Projectile turretBullet[1];
	bool shoot;
}turret;

typedef struct wall_s {
	int enable;
	int Pos_X;
	int Pos_Y;
	int health;
}wall;

turret turrets[6];
wall walls[6];

void towerUpdate(float dt);
void renderTower(void);
void buildTurret(void);
void buildWall(void);
void removeTowers(void);

