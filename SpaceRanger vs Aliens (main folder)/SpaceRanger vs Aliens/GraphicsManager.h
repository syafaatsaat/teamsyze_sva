#pragma once

#define SCREEN_WIDTH 150
#define SCREEN_HEIGHT 41

#include "GameManager.h"

void GraphicsManager_Init(void);

void Game_Render(float deltaTime);

void GraphicsManager_Exit(void);
