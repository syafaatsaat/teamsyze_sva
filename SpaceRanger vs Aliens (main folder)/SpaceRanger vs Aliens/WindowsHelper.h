#include <Windows.h>
#pragma once
/*Set the Desired Console title here*/
#define CONSOLE_TITLE "SpaceRanger Vs Aliens"

typedef enum TextColour_e
{
	WHITE = 0x0F,
	RED = 0x04,
	GREEN = 0x0A,
	BLUE = 0x01,
	YELLOW = 0x0E,
	PURPLE  = 0x05,
	GREY = 0x08
} TextColour;

void WindowsHelper_Init(void);
void WindowsHelper_SetCursorPosition(int x, int y);
void WindowsHelper_FullScreen(void);
void WindowsHelper_CustomScreen(int inputWidth, int inputHeight);
int WindowsHelper_GetConsoleWidth(void);
int WindowsHelper_GetConsoleHeight(void);
void WindowsHelper_ClearScreen(void);

/*New functions used for drawing. No more printf usage*/
void WindowsHelper_CreateOutputBuffer(void);
void WindowsHelper_CleanupOutputBuffer(void);
void WindowsHelper_DrawCharacterInPosition(WORD attribute, unsigned char character, int x, int y);
void WindowsHelper_DrawString(WORD attribute, char string[], int x_first_char, int y);
void WindowsHelper_ClearBuffer(void);
void WindowsHelper_DrawOutputBuffer(void);
void WindowsHelper_Exit(void);