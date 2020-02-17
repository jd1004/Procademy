#include <windows.h>
#include <stdio.h>
#include "console.h"

HANDLE handleConsole;

void ConsoleInitial()
{
	CONSOLE_CURSOR_INFO consoleCursor;

	// 커서 안보이게 설정
	consoleCursor.bVisible = FALSE;
	consoleCursor.dwSize = 1;

	// 콘솔화면 핸들 구하기
	handleConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handleConsole, &consoleCursor);
}


void ConsoleMoveCursor(int posX, int posY)
{
	COORD coord;
	coord.X = posX;
	coord.Y = posY;

	SetConsoleCursorPosition(handleConsole, coord);
}