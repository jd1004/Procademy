#include <windows.h>
#include <stdio.h>
#include "console.h"

HANDLE handleConsole;

void ConsoleInitial()
{
	CONSOLE_CURSOR_INFO consoleCursor;

	// Ŀ�� �Ⱥ��̰� ����
	consoleCursor.bVisible = FALSE;
	consoleCursor.dwSize = 1;

	// �ܼ�ȭ�� �ڵ� ���ϱ�
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