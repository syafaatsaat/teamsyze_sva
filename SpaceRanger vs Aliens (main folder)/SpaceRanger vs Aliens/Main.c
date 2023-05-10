#include "Includes.h"
#include "GameManager.h"
#include "Player.h"
#include "GraphicsManager.h"

int main(void)
{
	clock_t ticksThen, ticksNow;
	float deltaTime;
	ticksThen = clock();

	/* Initialise the renderer */
	GraphicsManager_Init();
	srand((unsigned int)time(NULL));

	/* Initialise the game and its states */
	Game_Init();
	
	/* Update the game and renderer */
	while(GetGameRunningState())
	{
		ticksNow = clock();
		deltaTime = (ticksNow - ticksThen) / (float)CLOCKS_PER_SEC;

		if (deltaTime >= 0.016f)
		{
			ticksThen = ticksNow;
			Game_Update(deltaTime);
			Game_Render(deltaTime);
		}		
	}

	GraphicsManager_Exit();
	
	return 0;
}