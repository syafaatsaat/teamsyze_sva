/***********************************************************************************
All content © 2018 DigiPen Institute of Technology Singapore, all rights reserved.

Filename:    Enemy.c
Author(s):   Syafaat (95%), Eric (5%)

Description/Features:
  This file handles the updating and rendering of the enemy. It controls how
  the enemies behave in the game, from their actions to their movements.
***********************************************************************************/

#include <stdio.h>
#include <Windows.h>
#include "WindowsHelper.h"
#include "Enemy.h"
#include "Player.h"
#include "Weapon.h"
#include "Powerups.h"

/* Initialize the spawn times in the specific wave times */
void Initialize_SpawnTimes(int index, Enemy* enemyWave, float *waveTime, int *firstIndex, int *lastIndex)
{
	/* this will be the limit timing of spawning */
	float waveLimit = *waveTime - 100.f;

	/* setting the spawning of the first two enemies during the second five seconds of the wave (design idea) */
	if (index >= *firstIndex && index <= *lastIndex)
		enemyWave->spawnTime = (float)(rand() % 5 + *waveTime);

	/* setting the spawning of the rest 25 enemies after that time all the way until the end of wave time */
	*firstIndex += 2;
	*lastIndex += 5;
	for (*waveTime -= 20.f; *waveTime >= waveLimit; *waveTime -= 20.f)
	{
		if (index >= *firstIndex && index <= *lastIndex)
			enemyWave->spawnTime = (float)(rand() % 20 + *waveTime);

		*firstIndex += 5;
		*lastIndex += 5;
	}
}

/*
This function initializes the enemy by it's type. There are 4 types.
Types of enemies: (speed is normally 25.f)
1) Normal alien with 100 health and normal speed (100%).
2) Self-healing alien with 75 health and third-quarter speed (150%).
3) Teleporting alien with 150 health and third-quarter speed (150%).
4) Tank alien with 200 health and half speed (50%).

So we are initializing their properties here.
*/
void Enemy_Init(int index, Enemy* enemyWave)
{
	int randomY = rand() % 6; /* getting a random number to determine which lane the enemy will spawn */
	int firstIndex = 0, lastIndex = 1; /* for Initialize_SpawnTimes which sets the limit of index numbers of enemies */
	float wave1Time = 470.f, wave2Time = 290.f, wave3Time = 110.f; /* the starting timing to spawn enemies in each wave */
	enemyWave->posX = 144; /* setting the enemy to spawn at the furthest end of the map */

	/* Line 61 to 71: calling Initialize_SpawnTimes to initialize the spawn times of enemies */
	firstIndex = 0; 
	lastIndex = 1;
	Initialize_SpawnTimes(index, enemyWave, &wave1Time, &firstIndex, &lastIndex);

	firstIndex = 27;
	lastIndex = 28;
	Initialize_SpawnTimes(index, enemyWave, &wave2Time, &firstIndex, &lastIndex);
	
	firstIndex = 54;
	lastIndex = 55;
	Initialize_SpawnTimes(index, enemyWave, &wave3Time, &firstIndex, &lastIndex);

	/* Line 74 to 90: initializing the enemy types by their spawn times */
	if (index <= 1)
		enemyWave->type = 1;

	if(index >= 2 && index <= 26)
		enemyWave->type = rand() % 2 + 1;

	if (index >= 27 && index <= 28)
		enemyWave->type = 3;

	if (index >= 29 && index <= 53)
		enemyWave->type = rand() % 3 + 1;

	if (index >= 54 && index <= 55)
		enemyWave->type = 4;

	if (index >= 56 && index <= 80)
		enemyWave->type = rand() % 4 + 1;

	/* Line 93 to 97: initializing the other enemy properties accordingly */
	enemyWave->gaveDrop = false;
	enemyWave->abilityTime = false;
	enemyWave->firstDown = false;
	enemyWave->reachedShipAlive = false;
	enemyWave->lastHitProjectileID = 0;

	/* determine which lane the enemy will spawn via randomY */
	switch (randomY)
	{
	case 0:
		enemyWave->posY = 3;
		break;
	case 1:
		enemyWave->posY = 7;
		break;
	case 2:
		enemyWave->posY = 11;
		break;
	case 3:
		enemyWave->posY = 15;
		break;
	case 4:
		enemyWave->posY = 19;
		break;
	case 5:
		enemyWave->posY = 23;
		break;
	default:
		enemyWave->posY = 3;
		break;
	}

	/* setting enemy properties according to their types */
	switch (enemyWave->type)
	{
	case 1:
		enemyWave->health = ALIEN_1_HEALTH;
		enemyWave->speed = ALIEN_1_SPEED;
		enemyWave->damage = ALIEN_1_DMG;
		enemyWave->cooldown = 0;
		enemyWave->deathStages = 5;
		break;
	case 2:
		enemyWave->health = ALIEN_2_HEALTH;
		enemyWave->speed = ALIEN_2_SPEED;
		enemyWave->damage = ALIEN_2_DMG;
		enemyWave->cooldown = ALIEN_2_COOLDOWN;
		enemyWave->deathStages = 5;
		break;
	case 3:
		enemyWave->health = ALIEN_3_HEALTH;
		enemyWave->speed = ALIEN_3_SPEED;
		enemyWave->damage = ALIEN_3_DMG;
		enemyWave->cooldown = ALIEN_3_COOLDOWN;
		enemyWave->deathStages = 4;
		break;
	case 4:
		enemyWave->health = ALIEN_4_HEALTH;
		enemyWave->speed = ALIEN_4_SPEED;
		enemyWave->damage = ALIEN_4_DMG;
		enemyWave->cooldown = ALIEN_4_COOLDOWN;
		enemyWave->deathStages = 9;
		break;
	}
}

/* 
This function renders the enemy position. It takes note of their spawn time so
they will only spawn when their time comes. 
*/
void Render_Enemy(Enemy *enemyWave, float *levelTime)
{
	/* If their spawn time is up, they will appear and render themselves on the screen. 
	   They will also render according to their positions. */
	if (enemyWave->spawnTime >= *levelTime)
	{
		TextColour current_colour;
		 /* Line 171 to 266: prints out the enemies accordingly. deathStages is to animate their death by erasing them pixel by pixel */
		if (enemyWave->type == 1)
		{
			if (!GetDeactivatedFreezePowerupState() && (enemyWave->spawnTime >= GetFreezeTime()))
				current_colour = BLUE; /* if they are frozen, they change to blue colour */
			else
				current_colour = RED; /* otherwise, they go back to their original colour */

			if(enemyWave->deathStages > 4)
				WindowsHelper_DrawCharacterInPosition(current_colour, (unsigned char)'‘', enemyWave->posX + 1, enemyWave->posY);

			if (enemyWave->deathStages > 3)
				WindowsHelper_DrawCharacterInPosition(current_colour, (unsigned char)'û', enemyWave->posX, enemyWave->posY + 1);

			if (enemyWave->deathStages > 2)
				WindowsHelper_DrawCharacterInPosition(current_colour, (unsigned char)'è', enemyWave->posX + 1, enemyWave->posY + 1);

			if (enemyWave->deathStages > 1)
				WindowsHelper_DrawCharacterInPosition(current_colour, (unsigned char)'û', enemyWave->posX + 2, enemyWave->posY + 1);

			if (enemyWave->deathStages > 0)
			WindowsHelper_DrawCharacterInPosition(current_colour, (unsigned char)'’', enemyWave->posX + 1, enemyWave->posY + 2);
		}
		else if (enemyWave->type == 2)
		{
			if (!GetDeactivatedFreezePowerupState() && (enemyWave->spawnTime >= GetFreezeTime()))
				current_colour = BLUE; /* if they are frozen, they change to blue colour */
			else
				current_colour = WHITE; /* otherwise, they go back to their original colour */

			if (enemyWave->deathStages > 4)
				WindowsHelper_DrawCharacterInPosition(current_colour, (unsigned char)'”', enemyWave->posX + 1, enemyWave->posY);

			if (enemyWave->deathStages > 3)
				WindowsHelper_DrawCharacterInPosition(current_colour, (unsigned char)'®', enemyWave->posX, enemyWave->posY + 1);

			if (enemyWave->deathStages > 2)
				WindowsHelper_DrawCharacterInPosition(current_colour, (unsigned char)'™', enemyWave->posX + 1, enemyWave->posY + 1);

			if (enemyWave->deathStages > 1)
				WindowsHelper_DrawCharacterInPosition(current_colour, (unsigned char)'¯', enemyWave->posX + 2, enemyWave->posY + 1);

			if (enemyWave->deathStages > 0)
				WindowsHelper_DrawCharacterInPosition(current_colour, (unsigned char)'V', enemyWave->posX + 1, enemyWave->posY + 2);
		}
		else if (enemyWave->type == 3)
		{
			if (!GetDeactivatedFreezePowerupState() && (enemyWave->spawnTime >= GetFreezeTime()))
				current_colour = BLUE; /* if they are frozen, they change to blue colour */
			else
				current_colour = YELLOW; /* otherwise, they go back to their original colour */

			if (enemyWave->deathStages > 3)
				WindowsHelper_DrawCharacterInPosition(current_colour, (unsigned char)'ï', enemyWave->posX + 1, enemyWave->posY);

			if (enemyWave->deathStages > 2)
				WindowsHelper_DrawCharacterInPosition(current_colour, (unsigned char)'À', enemyWave->posX, enemyWave->posY + 1);

			if (enemyWave->deathStages > 1)
				WindowsHelper_DrawCharacterInPosition(current_colour, (unsigned char)'Ž', enemyWave->posX + 1, enemyWave->posY + 1);

			if (enemyWave->deathStages > 0)
				WindowsHelper_DrawCharacterInPosition(current_colour, (unsigned char)'Ù', enemyWave->posX + 2, enemyWave->posY + 1);
		}
		else if (enemyWave->type == 4)
		{
			if (!GetDeactivatedFreezePowerupState() && (enemyWave->spawnTime >= GetFreezeTime()))
				current_colour = BLUE; /* if they are frozen, they change to blue colour */
			else 
				current_colour = PURPLE; /* otherwise, they go back to their original colour */

			if (enemyWave->deathStages > 8)
				WindowsHelper_DrawCharacterInPosition(current_colour, (unsigned char)'ª', enemyWave->posX, enemyWave->posY);

			if (enemyWave->deathStages > 7)
				WindowsHelper_DrawCharacterInPosition(current_colour, (unsigned char)'à', enemyWave->posX + 1, enemyWave->posY);

			if (enemyWave->deathStages > 6)
				WindowsHelper_DrawCharacterInPosition(current_colour, (unsigned char)'©', enemyWave->posX + 2, enemyWave->posY);

			if (enemyWave->deathStages > 5)
				WindowsHelper_DrawCharacterInPosition(current_colour, (unsigned char)'Ó', enemyWave->posX, enemyWave->posY + 1);

			if (enemyWave->deathStages > 4)
				WindowsHelper_DrawCharacterInPosition(current_colour, (unsigned char)'×', enemyWave->posX + 1, enemyWave->posY + 1);

			if (enemyWave->deathStages > 3)
				WindowsHelper_DrawCharacterInPosition(current_colour, (unsigned char)'½', enemyWave->posX + 2, enemyWave->posY + 1);

			if (enemyWave->deathStages > 2)
				WindowsHelper_DrawCharacterInPosition(current_colour, (unsigned char)'ß', enemyWave->posX, enemyWave->posY + 2);

			if (enemyWave->deathStages > 1)
				WindowsHelper_DrawCharacterInPosition(current_colour, (unsigned char)'Ð', enemyWave->posX + 1, enemyWave->posY + 2);

			if (enemyWave->deathStages > 0)
				WindowsHelper_DrawCharacterInPosition(current_colour, (unsigned char)'ß', enemyWave->posX + 2, enemyWave->posY + 2);
		}
	}
}

/* To render the loot drop when the enemies die */
void Render_Loot(Enemy *enemyWave)
{
	WindowsHelper_DrawCharacterInPosition(GREEN, (unsigned char)'ë', enemyWave->posX + 1, enemyWave->posY + 2);
}

/* This is the function that the game state calls to update the enemies one by one. */
void Enemy_Update(float *levelTime, Enemy *enemyWave, Projectile Player_Bullets[], int *resources, float *shipHealth, float dt)
{
	/* If the enemy is supposed to spawn at the current time, then they will spawn. */
	if (enemyWave->spawnTime >= *levelTime)
	{
		/* if the enemy is still alive */
		if (enemyWave->health > 0)
		{
			if (GetNumActivePlayerProjectiles() == 0)
				enemyWave->lastHitProjectileID = 0;

			/* holdPos is to make sure they move according to time and not speed through the map */
			enemyWave->holdPos += 1.f;
			/* also with the help of their own speed */
			if (enemyWave->holdPos > enemyWave->speed)
			{
				enemyWave->holdPos = 0.f;

				/* updates the turret behaviours in regards to the enemies */
				for (int i = 0; i < NumOfTurret; ++i) {
					if (turrets[i].enable == true) {
						if (turrets[i].Pos_Y == enemyWave->posY && turrets[i].Pos_X == enemyWave->posX) {
							turrets[i].enable = false;
						}
					}
				}

				/* if the enemy is still not at the spaceship yet */
				if (enemyWave->posX > 17)
				{
					/* updates their abilities and cooldowns */
					Enemy_Ability(enemyWave);
					/* some of them does not move due to their ability except the tank alien who charges forward */
					if (!enemyWave->abilityTime || enemyWave->type == 4)
					{
						/* If freeze powerup is not active, enemies will advance */
						if (GetDeactivatedFreezePowerupState() || (enemyWave->spawnTime < GetFreezeTime()))
							enemyWave->posX -= 1;
					}

					/* updates the wall behaviours in regards to the enemies */
					for (int i = 0; i < NumOfWall; ++i) {
						if (walls[i].enable == true) {
							if (walls[i].Pos_Y == enemyWave->posY && (walls[i].Pos_X + 3) == enemyWave->posX + 3) {
								walls[i].health -= (int)enemyWave->damage;
								enemyWave->posX += 1;
							}
						}
					}
				}
				else /* if the enemy has reached the spaceship */
				{
					*shipHealth -= enemyWave->damage; /* make it to inflict damage to the spaceship */
					enemyWave->reachedShipAlive = true; /* set reachedShipAlive to true to indicate they made it to the spaceship alive */
					enemyWave->health = 0; /* set their health to zero to 'kill' them */
					enemyWave->deathStages = 0; /* stop their death animation and dont render them at all because they did not die technically */
				}
			}

			/* Render the enemies. */
			Render_Enemy(enemyWave, levelTime);

			/* updates the turret behaviours in regards to the enemies */
			for (int i = 0; i < NumOfTurret; ++i) {
				if(turrets[i].enable == true){
					if (turrets[i].turretBullet[0].shoot == true) {
						if (turrets[i].turretBullet[0].Pos_Y == enemyWave->posY && turrets[i].turretBullet[0].Pos_X >= enemyWave->posX) {
							turrets[i].turretBullet[0].shoot = false;
							enemyWave->health -= TurretDmg;
						}
					}
				}
			}

			/* updates the bullet behaviours in regards to the enemies */
			for (int i = 0; i < PLAYER_BULLET; ++i) {
				if (Player_Bullets[i].shoot == true)
				{
					if (Player_Bullets[i].Pos_Y == enemyWave->posY && ((Player_Bullets[i].Pos_X == enemyWave->posX) || (Player_Bullets[i].Pos_X == enemyWave->posX + 1))
						&& (Player_Bullets[i].id != enemyWave->lastHitProjectileID)) {
						
						/* If shots are non-piercing, make them inactive once the enemy is hit */
						if (!GetPlayerWeaponPiercingShotsState())
							Player_Bullets[i].shoot = false;

						enemyWave->health -= GetPlayerWeaponDmg();

						enemyWave->lastHitProjectileID = Player_Bullets[i].id;
					}
				}
			}
		}
		else /* if the enemy dies / health = 0 */
		{
			/* Line 373 to 383: renders the death animation of the enemies */
			if (enemyWave->deathStages > 0)
			{
				Render_Enemy(enemyWave, levelTime);

				enemyWave->holdPos += (dt * 0.5f);

				if (enemyWave->holdPos > 0.1f)
				{
					enemyWave->holdPos = 0.f;
					enemyWave->deathStages -= 1;					
				}
			}
			else /* if their death animation is over */
			{
				/* if they die without reaching the spaceship, render the loot 
				   and updates the loot to move towards the spaceship */
				if (enemyWave->posX > 17)
				{
					enemyWave->posX -= 1;
					Render_Loot(enemyWave);
				}
				else /* otherwise, if they reached the spaceship alive, don't give loot to the player */
				{
					if (!enemyWave->gaveDrop && !enemyWave->reachedShipAlive) /* but if they die early, give loot to player */
					{
						enemyWave->gaveDrop = true;
						*resources += 5;
					}
				}
			}
		}
	}
}

/* This function handles the ability function of the enemies. */
void Enemy_Ability(Enemy *enemyWave)
{
	int i = 0, random = 0;
	enemyWave->cooldown -= 1; /* decrement the ability cooldown every second */

	/* checking if the cooldown is ready to trigger */
	if (enemyWave->cooldown <= 0)
	{
		/* self-healing alien does its thing */
		if (enemyWave->type == 2)
		{
			/* increases its health / heals itself */
			enemyWave->health += 5;
			enemyWave->cooldown = ALIEN_2_COOLDOWN;
			enemyWave->abilityTime = true;
			enemyWave->firstDown = true;
		}

		/* teleporting alien does its thing */
		if (enemyWave->type == 3)
		{
			random = rand() % 6;

			/* finds a random lane to teleport to */
			switch (random)
			{
			case 0:
				enemyWave->posY = 3;
				break;
			case 1:
				enemyWave->posY = 7;
				break;
			case 2:
				enemyWave->posY = 11;
				break;
			case 3:
				enemyWave->posY = 15;
				break;
			case 4:
				enemyWave->posY = 19;
				break;
			case 5:
				enemyWave->posY = 23;
				break;
			}
			
			enemyWave->cooldown = ALIEN_3_COOLDOWN;
			enemyWave->abilityTime = true;
			enemyWave->firstDown = true;
		}

		/* tank alien does its thing */
		if (enemyWave->type == 4)
		{
			/* charges forward / have limited time haste */
			enemyWave->speed = 10.f;
			enemyWave->cooldown = ALIEN_4_COOLDOWN;
			enemyWave->abilityTime = true;
			enemyWave->firstDown = true;
		}
	}

	/* firstDown is to not activate its ability animation when it just spawned */
	if (enemyWave->firstDown)
	{
		if (enemyWave->cooldown == ALIEN_2_COOLDOWN_LIMIT)
		{
			if (enemyWave->type == 2)
			{
				enemyWave->abilityTime = false;
			}
		}

		if (enemyWave->cooldown == ALIEN_3_COOLDOWN_LIMIT)
		{
			if (enemyWave->type == 3)
			{
				enemyWave->abilityTime = false;
			}
		}

		if (enemyWave->cooldown == ALIEN_4_COOLDOWN_LIMIT)
		{
			if (enemyWave->type == 4)
			{
				enemyWave->speed = ALIEN_4_SPEED;
				enemyWave->abilityTime = false;
			}
		}
	}	

	/* abilityTime is to trigger its ability animation */
	if (enemyWave->abilityTime)
	{
		if (enemyWave->type == 2)
		{
			WindowsHelper_DrawCharacterInPosition(WHITE, '+', enemyWave->posX - 2, enemyWave->posY);
			WindowsHelper_DrawCharacterInPosition(WHITE, '+', enemyWave->posX + 3, enemyWave->posY);
		}

		if (enemyWave->type == 4)
		{
			for (i = enemyWave->posX + 3; i < enemyWave->posX + 6; i++)
			{
				WindowsHelper_DrawCharacterInPosition(PURPLE, '~', i, enemyWave->posY);
				WindowsHelper_DrawCharacterInPosition(PURPLE, '~', i, enemyWave->posY + 1);
				WindowsHelper_DrawCharacterInPosition(PURPLE, '~', i, enemyWave->posY + 2);
			}
		}
	}
}