/***********************************************************************************
All content © 2018 DigiPen Institute of Technology Singapore, all rights reserved.

Filename:    Weapon.c
Author(s):   Eric Aw (100%)
Logins(s):	 yuhliangeric.a
Course:		 GAM100

Description/Features:
  This file contains anything relating to the player's weapon and it's stats, as
  well as functions pertaining weapon upgrades/player abilities. Some getter and
  setter functions are also here for specific weapon stats.
***********************************************************************************/

#include "Includes.h"
#include "WindowsHelper.h"
#include "Weapon.h"
#include "Player.h"
#include "GameStateLevel1.h"
#include "GameLevel.h"
#include "Powerups.h"

Weapon playerWeapon;	/* The player's weapon (struct) */


/* Initialise all weapon-related variables */
void InitWeapon(void)
{
	playerWeapon.base_damage = STARTING_BASE_DMG;

	playerWeapon.base_firerate = STARTING_BASE_FIRERATE;
	playerWeapon.canFire = true;
	playerWeapon.firerate_timer = 0.f;

	playerWeapon.autoFireMode = false;

	playerWeapon.piercingShotsMode = false;
}


/* Update weapon-related timings (fire-rate of weapon) */
void UpdateWeaponStatTimers(float dt)
{
	if (playerWeapon.firerate_timer > 0.f)
	{
		playerWeapon.firerate_timer -= (0.5f * dt);

		playerWeapon.canFire = false;
	}
	else
		playerWeapon.canFire = true;
}


/* Returns a pointer to the player's weapon */
struct Weapon_s *GetPlayerWeaponPtr(void)
{
	return &playerWeapon;
}


/* Returns the player weapon's base damage */
int GetPlayerWeaponDmg(void)
{
	return playerWeapon.base_damage;
}


/* Sets the player weapon's base damage */
void SetPlayerWeaponDmg(int input)
{
	playerWeapon.base_damage = input;
}


/* Returns the player weapon's base fire-rate */
float GetPlayerWeaponFirerate(void)
{
	return playerWeapon.base_firerate;
}


/* Sets the player weapon's base fire-rate */
void SetPlayerWeaponFirerate(float input)
{
	playerWeapon.base_firerate = input;
}


/* Returns the player weapon's ability to fire right now (fire-rate related) */
bool GetPlayerWeaponCanFire(void)
{
	return playerWeapon.canFire;
}


/* Resets the player weapon's "cool-down" period  (fire-rate related) */
void ResetPlayerWeaponCooldownTimer(void)
{
	playerWeapon.firerate_timer = (1 / playerWeapon.base_firerate);
}


/* Returns the player weapon's auto-fire mode */
bool GetPlayerWeaponAutoFireState(void)
{
	return playerWeapon.autoFireMode;
}


/* Sets the player weapon's auto-fire mode */
void SetPlayerWeaponAutoFireState(bool input)
{
	playerWeapon.autoFireMode = input;
}


/* Returns the player weapon's piercing shot mode */
bool GetPlayerWeaponPiercingShotsState(void)
{
	return playerWeapon.piercingShotsMode;
}


/* Sets the player weapon's piercing shot mode */
void SetPlayerWeaponPiercingShotsState(bool input)
{
	playerWeapon.piercingShotsMode = input;
}