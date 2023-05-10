/***********************************************************************************
All content © 2018 DigiPen Institute of Technology Singapore, all rights reserved.

Filename:    Store.c
Author(s):   Eric Aw (100%)
Logins(s):	 yuhliangeric.a
Course:		 GAM100

Description/Features:
  This file contains anything relating to the store, and the handling of the weapon
  upgrades or power-ups that can be purchased by the player, as well as the printing
  of messages pertaining player interaction with the store.
***********************************************************************************/

#include "Includes.h"
#include "WindowsHelper.h"
#include "Store.h"
#include "Player.h"
#include "GameStateLevel1.h"
#include "GameLevel.h"
#include "Weapon.h"
#include "Tower.h"
#include "Powerups.h"

enum PowerupType theCurrentlySelectedPowerup;	/* The current powerup being selected and viewed in the store */

bool piercingShotsBought;						/* If piercing shots upgrade has been bought */
bool autoFireBought;							/* If auto-fire upgrade has been bought */

int theCurrentWave;								/* The current wave */

/* Initialise store-related variables and ensure that the store message window is "cleared" */
void InitStore(void)
{
	theCurrentlySelectedPowerup = TURRET;

	piercingShotsBought = false;
	autoFireBought = false;
	
	theCurrentWave = GetWaveNum();

	DisplayStoreMessage("");
}


/* Purchase a specified powerup and apply effects/abilities on the player */
void Store_PurchaseSelectedItem(int *resources, float *theShipHealth)
{
	switch (theCurrentlySelectedPowerup)
	{
		/* Builds a turret which fires at enemies */
		case TURRET:
			if (turrets[playerTile].enable)
				DisplayStoreMessage("This lane already has a turret!");
			else if (*resources < TURRET_COST)
				DisplayStoreMessage("Not enough crystals...");
			else
			{
				DisplayStoreMessage("Turret built!");

				*resources -= TURRET_COST;

				/*  Build a turret */
				buildTurret();
			}
			break;

		/* Builds a wall which blocks enemies */
		case WALL:
			if (walls[playerTile].enable)
				DisplayStoreMessage("This lane already has a wall!");
			else if (*resources < WALL_COST)
				DisplayStoreMessage("Not enough crystals...");
			else
			{
				DisplayStoreMessage("Wall built!");

				*resources -= WALL_COST;

				/*  Build a wall */
				buildWall();
			}
			break;

		/* Increases the ship's health */
		case SHIPHEALTH_INCR:
			/* If the player's ship is at full health */
			if (*theShipHealth == SHIP_MAX_HEALTH)
				DisplayStoreMessage("Ship is already in good condition!");
			else if (*resources < SHIPHEALTH_INCR_COST)
				DisplayStoreMessage("Not enough crystals...");
			else
			{
				DisplayStoreMessage("Ship repair purchased!");

				*resources -= SHIPHEALTH_INCR_COST;

				/* Increase the health of the ship */
				if (*theShipHealth <= (SHIP_MAX_HEALTH - SHIPHEALTH_INCR_AMOUNT))
					*theShipHealth += SHIPHEALTH_INCR_AMOUNT;
				else
					*theShipHealth = SHIP_MAX_HEALTH;
			}
			break;

		/* Increases the player's weapon damage */
		case WEAP_DMG_INCR:
			if (*resources < WEAP_DMG_INCR_COST)
				DisplayStoreMessage("Not enough crystals...");
			else
			{
				DisplayStoreMessage("Weapon damage upgraded.");

				*resources -= WEAP_DMG_INCR_COST;

				/* Increase the weapon damage of the player */
				if (GetDeactivatedInstaKillPowerupState())
					SetPlayerWeaponDmg(GetPlayerWeaponDmg() + WEAP_DMG_INCR_AMOUNT);
				else
					SetPlayerWeaponDmgTemp(GetPlayerWeaponDmgTemp() + WEAP_DMG_INCR_AMOUNT);
			}
			break;

		/* Increases the player's weapon fire-rate */
		case WEAP_FIRERATE_INCR:
			if (*resources < WEAP_FIRERATE_INCR_COST)
				DisplayStoreMessage("Not enough crystals...");
			else
			{
				DisplayStoreMessage("Weapon fire-rate upgraded.");

				*resources -= WEAP_FIRERATE_INCR_COST;

				/* Increase the weapon fire-rate of the player */
				SetPlayerWeaponFirerate(GetPlayerWeaponFirerate() + WEAP_FIRERATE_INCR_AMOUNT);
			}
			break;

		/* Allows the player to fire piercing shots */
		case WEAP_PIERCINGSHOTS:
			if (theCurrentWave < WEAP_PIERCINGSHOTS_WAVE_UNLOCK)
				DisplayStoreMessage("This has not been unlocked yet!");
			else if (piercingShotsBought)
				DisplayStoreMessage("You already bought this!");
			else if (*resources < WEAP_PIERCINGSHOTS_COST)
				DisplayStoreMessage("Not enough crystals...");
			else
			{
				DisplayStoreMessage("Piercing shots upgrade purchased.");

				*resources -= WEAP_PIERCINGSHOTS_COST;

				/* Enable the firing of piercing shots by the player's weapon */
				SetPlayerWeaponPiercingShotsState(true);

				piercingShotsBought = true;
			}
			break;

		/* Allows the player to auto-fire */
		case WEAP_AUTOFIRE:
			if (autoFireBought)
				DisplayStoreMessage("You already bought this!");
			else if (*resources < WEAP_AUTOFIRE_COST)
				DisplayStoreMessage("Not enough crystals...");
			else
			{
				DisplayStoreMessage("Auto-fire upgrade purchased.");

				*resources -= WEAP_AUTOFIRE_COST;

				/* Enable auto-firing of the player's weapon */
				SetPlayerWeaponAutoFireState(true);

				autoFireBought = true;
			}
			break;

		/* Gives the player the ability to shoot and kill enemies instantly with a single shot (for a limited time) */
		case POWERUP_INSTAKILL:
			if (theCurrentWave < POWERUP_INSTAKILL_WAVE_UNLOCK)
				DisplayStoreMessage("This has not been unlocked yet!");
			else if (!GetDeactivatedInstaKillPowerupState())
				DisplayStoreMessage("Insta-kill is already active!");
			else if (*resources < POWERUP_INSTAKILL_COST)
				DisplayStoreMessage("Not enough crystals...");
			else
			{
				DisplayStoreMessage("Insta-kill time! Oh yeah!");

				*resources -= POWERUP_INSTAKILL_COST;

				/* Enable insta-kill mode (for 15 seconds) */
				ActivateInstaKillPowerup();
			}
			break;

		/* Freezes all active enemies on screen (for a limited time) */
		case POWERUP_FREEZE:
			if (!GetDeactivatedInstaKillPowerupState())
				DisplayStoreMessage("Freeze is already active!");
			else if (*resources < POWERUP_FREEZE_COST)
				DisplayStoreMessage("Not enough crystals...");
			else
			{
				DisplayStoreMessage("Froze all active enemies!");

				*resources -= POWERUP_FREEZE_COST;

				/* Freeze all enemies (for 7.5 seconds) */
				ActivateFreezePowerup();
			}
			break;

		default:
			break;
	}
}


/* Handle the rendering of UI relating to the store, such as the currently selected item
   and the output store messages */
void RenderStoreUI(float *theTimer, float *theStoreMsgDisplayStart, char (*theStoreMsg) [40])
{
	switch (GetCurrentlySelectedPowerup())
	{
	case TURRET:
		WindowsHelper_DrawString(0x0F, "BUILD TURRET", STORE_ITEM_DESCRIPTION_POSX + 2, 36);
		WindowsHelper_DrawString(0x0F, "(COST: 15)", STORE_ITEM_DESCRIPTION_POSX + 3, 37);
		break;

	case WALL:
		WindowsHelper_DrawString(0x0F, "BUILD WALL", STORE_ITEM_DESCRIPTION_POSX + 3, 36);
		WindowsHelper_DrawString(0x0F, "(COST: 10)", STORE_ITEM_DESCRIPTION_POSX + 3, 37);
		break;

	case SHIPHEALTH_INCR:
		WindowsHelper_DrawString(0x0F, "REPAIR SHIP", STORE_ITEM_DESCRIPTION_POSX + 2, 36);
		WindowsHelper_DrawString(0x0F, "(COST: 10)", STORE_ITEM_DESCRIPTION_POSX + 3, 37);
		break;

	case WEAP_DMG_INCR:
		WindowsHelper_DrawString(0x0F, "DAMAGE+", STORE_ITEM_DESCRIPTION_POSX + 4, 36);
		WindowsHelper_DrawString(0x0F, "(COST: 25)", STORE_ITEM_DESCRIPTION_POSX + 3, 37);
		break;

	case WEAP_FIRERATE_INCR:
		WindowsHelper_DrawString(0x0F, "FIRE-RATE+", STORE_ITEM_DESCRIPTION_POSX + 3, 36);
		WindowsHelper_DrawString(0x0F, "(COST: 15)", STORE_ITEM_DESCRIPTION_POSX + 3, 37);
		break;

	case WEAP_PIERCINGSHOTS:
		WindowsHelper_DrawString(0x0F, "PIERCING SHOTS", STORE_ITEM_DESCRIPTION_POSX + 1, 36);
		WindowsHelper_DrawString(0x0F, "(COST: 35)", STORE_ITEM_DESCRIPTION_POSX + 3, 37);
		break;

	case WEAP_AUTOFIRE:
		WindowsHelper_DrawString(0x0F, "AUTO-FIRE", STORE_ITEM_DESCRIPTION_POSX + 3, 36);
		WindowsHelper_DrawString(0x0F, "(COST: 30)", STORE_ITEM_DESCRIPTION_POSX + 3, 37);
		break;

	case POWERUP_INSTAKILL:
		WindowsHelper_DrawString(0x0F, "INSTA-KILL MODE", STORE_ITEM_DESCRIPTION_POSX, 36);
		WindowsHelper_DrawString(0x0F, "(COST: 40)", STORE_ITEM_DESCRIPTION_POSX + 3, 37);
		break;

	case POWERUP_FREEZE:
		WindowsHelper_DrawString(0x0F, "FREEZE ENEMIES", STORE_ITEM_DESCRIPTION_POSX + 1, 36);
		WindowsHelper_DrawString(0x0F, "(COST: 25)", STORE_ITEM_DESCRIPTION_POSX + 3, 37);
		break;

	default:
		WindowsHelper_DrawString(0x0F, "???", STORE_ITEM_DESCRIPTION_POSX + 5, 36);
		break;
	}

	/* Display of store messages, according to the timer */
	if (*theTimer > (*theStoreMsgDisplayStart - MAX_STORE_MSG_DISP_TIME))
		WindowsHelper_DrawString(0x0F, *theStoreMsg, STORE_MSG_POSX, STORE_MSG_POSY);
	else
		WindowsHelper_DrawString(0x0F, "", STORE_MSG_POSX, STORE_MSG_POSY);

	/* Update and display store item unlock messages */
	if (theCurrentWave != GetWaveNum())
	{
		theCurrentWave = GetWaveNum();

		switch (theCurrentWave)
		{
		case POWERUP_INSTAKILL_WAVE_UNLOCK:
			DisplayStoreMessage("Insta-Kill powerup unlocked!");
			break;

		case WEAP_PIERCINGSHOTS_WAVE_UNLOCK:
			DisplayStoreMessage("Piercing shots upgrade unlocked!");
			break;
		}
	}
}


/* Switches to the next store item */
void Store_NextSelection(void)
{
	if (theCurrentlySelectedPowerup == NUM_POWERUPS - 1)
		theCurrentlySelectedPowerup = 0;
	else
		theCurrentlySelectedPowerup++;
}


/* Switches to the previous store item */
void Store_PreviousSelection(void)
{
	if (theCurrentlySelectedPowerup == 0)
		theCurrentlySelectedPowerup = NUM_POWERUPS - 1;
	else
		theCurrentlySelectedPowerup--;
}


/* Getter function that returns the currently-selected powerup in the store */
enum Powerup GetCurrentlySelectedPowerup(void)
{
	return theCurrentlySelectedPowerup;
}