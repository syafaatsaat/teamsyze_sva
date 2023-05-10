#pragma once

#include "Player.h"
#include "Weapon.h"

#define STORE_MSG_POSX 51
#define STORE_MSG_POSY 37
#define STORE_ITEM_DESCRIPTION_POSX 109
#define MAX_STORE_MSG_DISP_TIME 3.5f

#define TURRET_COST 15

#define WALL_COST 10

#define SHIPHEALTH_INCR_COST 10
#define SHIPHEALTH_INCR_AMOUNT 20.f

#define WEAP_DMG_INCR_COST 25
#define WEAP_DMG_INCR_AMOUNT 10

#define WEAP_FIRERATE_INCR_COST 15
#define WEAP_FIRERATE_INCR_AMOUNT 1.f

#define WEAP_PIERCINGSHOTS_COST 35
#define WEAP_PIERCINGSHOTS_WAVE_UNLOCK 3

#define WEAP_AUTOFIRE_COST 30

#define POWERUP_INSTAKILL_COST 40
#define POWERUP_INSTAKILL_WAVE_UNLOCK 2

#define POWERUP_FREEZE_COST 25

enum PowerupType
{
	TURRET,
	WALL,
	SHIPHEALTH_INCR,
	WEAP_DMG_INCR,
	WEAP_FIRERATE_INCR,
	WEAP_AUTOFIRE,
	POWERUP_FREEZE,
	POWERUP_INSTAKILL,
	WEAP_PIERCINGSHOTS,
	NUM_POWERUPS
};

void InitStore(void);
void Store_PurchaseSelectedItem(int *resources, float *theShipHealth);
void RenderStoreUI(float *theTimer, float *theStoreMsgDisplayStart, char (*theStoreMsg) [40]);
void Store_NextSelection(void);
void Store_PreviousSelection(void);
enum Powerup GetCurrentlySelectedPowerup(void);
