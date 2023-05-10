#include "Includes.h"
#include "WindowsHelper.h"

/*Variables used to handle Windows stuff, not exposed to other parts of the game*/
static HANDLE wHnd;    /* Handle to write to the console.*/
static HANDLE rHnd;    /* Handle to read from the console.*/
HWND theConsoleWindow;
static CHAR_INFO * outputBuffer;	/*Buffer for all things that need to be drawn*/
static int bufferSize;	/*Size of the allocated buffer, in bytes*/
static SMALL_RECT writeArea; /*Area specified for drawing the output buffer*/
static COORD bufferPosition; /*Starting point of where the output buffer should start reading from*/
static COORD bufferDimensions;	/*Dimensions of the output buffer*/

/*Always call this function first before any other WindowsHelper functions*/
void WindowsHelper_Init(void)
{
	theConsoleWindow = GetConsoleWindow();
	SetWindowLong(theConsoleWindow, GWL_STYLE, GetWindowLong(theConsoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleTitle(TEXT(CONSOLE_TITLE));

	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 100;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(wHnd, &cursorInfo);

	WindowsHelper_CreateOutputBuffer();
}

/*Sets the console cursor position. Note that (0,0) is the top left of the console*/
void WindowsHelper_SetCursorPosition(int x, int y)
{
	COORD center;
	center.X = (short)x;
	center.Y = (short)y;
	SetConsoleCursorPosition(wHnd, center);
}

/*Wrapper to the function*/
void WindowsHelper_GetLargestConsoleWindowSize(int *width, int* height)
{
	if (width == NULL || height == NULL)
	{
		return;
	}

	COORD size = GetLargestConsoleWindowSize(wHnd);
	/*Dereferncing pointers to assign integer values into the integers being pointed at */
	*width = size.X;
	*height = size.Y;
}

/*Setting the window to be as big as possible*/
void WindowsHelper_FullScreen(void)
{
	int width = 0, height = 0;
	WindowsHelper_GetLargestConsoleWindowSize(&width, &height);

	COORD bufferSizeTemp;
	bufferSizeTemp.X = (short)width;
	bufferSizeTemp.Y = (short)height;
	SetConsoleScreenBufferSize(wHnd, bufferSizeTemp);

	SMALL_RECT windowSize;
	windowSize.Left = (short)0;
	windowSize.Top = (short)0;
	windowSize.Right = (short)width - 1;
	windowSize.Bottom = (short)height - 1;
	SetConsoleWindowInfo(wHnd, 1, &windowSize);

	WindowsHelper_CleanupOutputBuffer();
	WindowsHelper_CreateOutputBuffer();
}

/*Setting the window's size to that specified to the function */
void WindowsHelper_CustomScreen(int inputWidth, int inputHeight)
{
	COORD bufferSizeTemp;
	bufferSizeTemp.X = (short)inputWidth;
	bufferSizeTemp.Y = (short)inputHeight;
	SetConsoleScreenBufferSize(wHnd, bufferSizeTemp);

	SMALL_RECT windowSize;
	windowSize.Left = (short)0;
	windowSize.Top = (short)0;
	windowSize.Right = (short)inputWidth - 1;
	windowSize.Bottom = (short)inputHeight - 1;
	SetConsoleWindowInfo(wHnd, 1, &windowSize);

	WindowsHelper_CleanupOutputBuffer();
	WindowsHelper_CreateOutputBuffer();
}

/*Clears everything in the console window and sets the cursor to position (0,0)*/
void WindowsHelper_ClearScreen(void)
{
	system("cls");
}

int WindowsHelper_GetConsoleWidth(void)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(wHnd, &csbi);
	return csbi.dwSize.X;
}

int WindowsHelper_GetConsoleHeight(void)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(wHnd, &csbi);
	return csbi.dwSize.Y;
}

/*New function to draw a character in a position of the buffer, attribute determines the color*/
void WindowsHelper_DrawCharacterInPosition(WORD attribute, unsigned char character, int x, int y)
{
	if (outputBuffer == 0 ||
		x < 0 ||
		x > bufferDimensions.X - 1 ||
		y < 0 ||
		y > bufferDimensions.Y - 1)
	{
		return;
	}
	else
	{
		int coordinate = y * bufferDimensions.X + x;
		outputBuffer[coordinate].Attributes = attribute;
		outputBuffer[coordinate].Char.AsciiChar = character;
	}
}

/* Function that draws a string starting from a position of the buffer */
void WindowsHelper_DrawString(WORD attribute, char string [], int x_first_char, int y)
{
	int i = 0;
	int x = x_first_char;
	int x_end = x + (int) strlen(string);

	for (; x < x_end; i++, x++)
		WindowsHelper_DrawCharacterInPosition(attribute, string[i], x, y);
}

/*Clears all information within the buffer*/
void WindowsHelper_ClearBuffer(void)
{
	if (outputBuffer == 0)
	{
		return;
	}
	memset(outputBuffer, 0, bufferSize);
}

/*Allocates the outputBuffer based on the console dimensions*/
void WindowsHelper_CreateOutputBuffer(void)
{
	if (outputBuffer != 0)
	{
		return;
	}
	bufferDimensions.X = (short)WindowsHelper_GetConsoleWidth();
	bufferDimensions.Y = (short)WindowsHelper_GetConsoleHeight();
	bufferSize = bufferDimensions.X * bufferDimensions.Y * sizeof(CHAR_INFO);
	outputBuffer = malloc(bufferSize);
	WindowsHelper_ClearBuffer();

	/*We are going to draw the entire screen with this buffer.
	If you wish to draw a specific portion of the screen, update this structure
	before WriteConsoleOutputA is called*/
	writeArea.Bottom = bufferDimensions.Y - 1;
	writeArea.Right = bufferDimensions.X - 1;
}

/*Cleans up memory allocated for the outputBuffer*/
void WindowsHelper_CleanupOutputBuffer(void)
{
	if (outputBuffer == 0)
	{
		return;
	}
	free(outputBuffer);
	outputBuffer = 0;
}

/*We will use this instead of printf now. Solves the flickering problem*/
void WindowsHelper_DrawOutputBuffer(void)
{
	if (outputBuffer == 0)
	{
		return;
	}
	/*Use the outputBuffer to draw on the console*/
	WriteConsoleOutputA(wHnd, outputBuffer, bufferDimensions, bufferPosition, &writeArea);
}

/*Exit function to release memory allocated*/
void WindowsHelper_Exit(void)
{
	WindowsHelper_CleanupOutputBuffer();
}