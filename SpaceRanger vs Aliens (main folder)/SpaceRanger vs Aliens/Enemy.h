/***********************************************************************************
All content © 2018 DigiPen Institute of Technology Singapore, all rights reserved.

Filename:    Enemy.h
Author(s):   Syafaat (95%), Eric (5%)

Description/Features:
  This file handles the updating and rendering of the enemy. It controls how
  the enemies behave in the game, from their actions to their movements.
***********************************************************************************/
#pragma once
#include "Projectiles.h"
#include "Player.h"
#include "Weapon.h"
#include "Tower.h"

#define ENEMY_WAVE_SIZE 81

#define ALIEN_1_HEALTH 100
#define ALIEN_1_SPEED 25.f
#define ALIEN_1_DMG 10.f

#define ALIEN_2_HEALTH 75
#define ALIEN_2_SPEED 20.f
#define ALIEN_2_DMG 8.f
#define ALIEN_2_COOLDOWN 10
#define ALIEN_2_COOLDOWN_LIMIT 8

#define ALIEN_3_HEALTH 150
#define ALIEN_3_SPEED 20.f
#define ALIEN_3_DMG 5.f
#define ALIEN_3_COOLDOWN 15
#define ALIEN_3_COOLDOWN_LIMIT 14

#define ALIEN_4_HEALTH 200
#define ALIEN_4_SPEED 50.f
#define ALIEN_4_DMG 15.f
#define ALIEN_4_COOLDOWN 15
#define ALIEN_4_COOLDOWN_LIMIT 10

/*
Enemy struct that holds the properties of the enemy.
1) x-position
2) y-position
3) type
4) health
5) speed
6) spawn time
7) hold position
8) damage
9) cooldown
10) gave drop
*/
typedef
struct
{
	int posX;
	int posY;
	int type;
	int health;
	float speed;
	float spawnTime;
	float holdPos;
	float damage;
	int cooldown;
	int lastHitProjectileID;
	int deathStages;
	bool gaveDrop;
	bool abilityTime;
	bool firstDown;
	bool reachedShipAlive;
} Enemy;

void Initialize_SpawnTimes(int index, Enemy* enemyWave, float *waveTime, int *firstIndex, int *lastIndex);

/*
This function initializes the enemy by it's type. There are 4 types.
So we are initializing their health and speed by their type.
*/
void Enemy_Init(int index, Enemy* enemyWave);

/*
This function renders the enemy position. It takes note of their spawn time so
they will only spawn when their time comes.
*/
void Render_Enemy(Enemy *enemyWave, float *levelTime);

void Render_Loot(Enemy *enemyWave);

/* This is the function that the game state calls to update the enemies one by one. */
void Enemy_Update(float *levelTime, Enemy *enemyWave, Projectile Player_Bullets[], int *resources, float *shipHealth, float dt);

/* This function handles the ability function of the enemies. */
void Enemy_Ability(Enemy *enemyWave);