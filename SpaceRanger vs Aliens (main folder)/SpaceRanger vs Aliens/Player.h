/***********************************************************************************
All content © 2018 DigiPen Institute of Technology Singapore, all rights reserved.

Filename    Player.h
Author      Chua Zun Sheng
DP email    zunsheng.chua@digipen.edu
Course      GAM100

Brief Description:
	The struct and functions prototype of player.c
***********************************************************************************/
#pragma once
#define LEVEL_TIME_MAX 481.f
#define WAVE_TIME_MAX 120.f
#define REST_TIME_MAX 60.f
#define SHIP_MAX_HEALTH 200.f
#define RESOURCES_STARTING_AMT 0
#define COLOUR_CHANGE_DURATION 0.125f

#include "Projectiles.h"

typedef struct Player_s {
	int Pos_X;
	int Pos_Y;
}Player;

Projectile Player_Bullet[PLAYER_BULLET];

void Player_Init(void);
void Player_Update(float dt);
void Render_Player(void);
int Get_PlayerPosX(void);
int Get_PlayerPosY(void);
void Set_PlayerPosX(int Pos_X);
void Set_PlayerPosY(int Pos_Y);
Player *Get_PlayerStruct(void);

int playerTile;