#pragma once

#define STARTING_BASE_DMG 20
#define STARTING_BASE_FIRERATE 2.f

#include "Player.h"

/* Struct of weapon stats */
typedef struct Weapon_s
{
	int base_damage;
	float base_firerate;
	bool canFire;
	float firerate_timer;
	bool autoFireMode;
	bool piercingShotsMode;
} Weapon;

void InitWeapon(void);
void UpdateWeaponStatTimers(float dt);
struct Weapon_s *GetPlayerWeaponPtr(void);
int GetPlayerWeaponDmg(void);
void SetPlayerWeaponDmg(int input);
float GetPlayerWeaponFirerate(void);
void SetPlayerWeaponFirerate(float input);
bool GetPlayerWeaponCanFire(void);
void ResetPlayerWeaponCooldownTimer(void);
bool GetPlayerWeaponAutoFireState(void);
void SetPlayerWeaponAutoFireState(bool input);
bool GetPlayerWeaponPiercingShotsState(void);
void SetPlayerWeaponPiercingShotsState(bool input);