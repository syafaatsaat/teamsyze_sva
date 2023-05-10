/***********************************************************************************
All content © 2018 DigiPen Institute of Technology Singapore, all rights reserved.

Filename:    Powerups.c
Author(s):   Eric Aw (100%)
Logins(s):	 yuhliangeric.a
Course:		 GAM100

Description/Features:
  This file contains anything relating to store-bought powerups and player abilities
  as well as functions pertaining the activation and updating of such powerups.
***********************************************************************************/

#include "Includes.h"
#include "WindowsHelper.h"
#include "Powerups.h"
#include "Player.h"
#include "GameStateLevel1.h"
#include "GameLevel.h"
#include "Weapon.h"

float instaKillPowerupTimer;		/* Timer that keeps track of the Insta-Kill powerup state */
int playerWeapon_base_dmg_temp;		/* Temporary variable that stores the player weapon's base damage */
bool alreadySetInstaKillDmg;		/* Boolean that checks if the Insta-Kill damage boost has been given to the player */
bool deactivatedInstaKillPowerup;	/* Boolean that checks if the Insta-Kill powerup has been deactivated or activated */

float freezePowerupTimer;			/* Timer that keeps track of the Freeze powerup state */
bool deactivatedFreezePowerup;		/* Boolean that checks if the Freeze powerup has been deactivated or activated */
float freezeTime;					/* Variable that specifies the timer which the enemies should be frozen by */


/* Initialise all powerup-related variables */
void InitPowerups(void)
{
	instaKillPowerupTimer = 0.f;
	playerWeapon_base_dmg_temp;
	alreadySetInstaKillDmg = false;
	deactivatedInstaKillPowerup = true;

	freezePowerupTimer = 0.f;
	deactivatedFreezePowerup = true;
	freezeTime = 0.f;
}


/* Update powerup-related timings (e.g. Insta-Kill powerup, Freeze powerup) */
void UpdatePowerupTimers(float dt)
{
	if (instaKillPowerupTimer > 0.f)
	{
		instaKillPowerupTimer -= (0.5f * dt);

		if (!alreadySetInstaKillDmg)
		{
			SetPlayerWeaponDmg(INSTAKILL_POWERUP_DMG);

			alreadySetInstaKillDmg = true;
		}

		deactivatedInstaKillPowerup = false;
	}
	else if (!deactivatedInstaKillPowerup)
	{
		SetPlayerWeaponDmg(playerWeapon_base_dmg_temp);

		alreadySetInstaKillDmg = false;

		deactivatedInstaKillPowerup = true;
	}

	if (freezePowerupTimer > 0.f)
	{
		freezePowerupTimer -= (0.5f * dt);

		deactivatedFreezePowerup = false;
	}
	else if (!deactivatedFreezePowerup)
		deactivatedFreezePowerup = true;
}


/* Activates the Insta-Kill powerup (shots kill enemies instantly) */
void ActivateInstaKillPowerup(void)
{
	playerWeapon_base_dmg_temp = GetPlayerWeaponDmg();

	instaKillPowerupTimer = INSTAKILL_POWERUP_DURATION;
}


/* Activates the Freeze powerup (freezes all active, onscreen enemies) */
void ActivateFreezePowerup(void)
{
	freezeTime = GetLevelTime();

	freezePowerupTimer = FREEZE_POWERUP_DURATION;
}


/* Returns the state of the Insta-Kill powerup (if it is currently inactive) */
bool GetDeactivatedInstaKillPowerupState(void)
{
	return deactivatedInstaKillPowerup;
}


/* Returns the Insta-Kill powerup's active time left */
float GetInstaKillPowerupTimer(void)
{
	return instaKillPowerupTimer;
}


/* Returns the temporarily-stored player weapon's base damage */
int GetPlayerWeaponDmgTemp(void)
{
	return playerWeapon_base_dmg_temp;
}


/* Sets the temporarily-stored player weapon's base damage */
void SetPlayerWeaponDmgTemp(int input)
{
	playerWeapon_base_dmg_temp = input;
}


/* Returns the state of the Freeze powerup (if it is currently inactive) */
bool GetDeactivatedFreezePowerupState(void)
{
	return deactivatedFreezePowerup;
}


/* Returns the Freeze powerup's active time left */
float GetFreezeTime(void)
{
	return freezeTime;
}