#pragma once

#define INSTAKILL_POWERUP_DURATION 15.f
#define INSTAKILL_POWERUP_DMG 1000

#define FREEZE_POWERUP_DURATION 7.5f

void InitPowerups(void);

void UpdatePowerupTimers(float dt);

void ActivateInstaKillPowerup(void);
bool GetDeactivatedInstaKillPowerupState(void);
float GetInstaKillPowerupTimer(void);

int GetPlayerWeaponDmgTemp(void);
void SetPlayerWeaponDmgTemp(int input);

void ActivateFreezePowerup(void);
bool GetDeactivatedFreezePowerupState(void);
float GetFreezeTime(void);
