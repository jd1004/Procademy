#pragma once

// Windows 콘솔 화면 커서 제어

#ifndef __CONSOLE__
#define __CONSOLE__



#define SCREEN_WIDTH 91			// 콘솔 가로 + NULL
#define SCREEN_HEIGHT 34		// 콘솔 세로


// 콘솔 제어 준비
void ConsoleInitial();

// 콘솔 화면 커서 X, Y 좌표로 이동
void ConsoleMoveCursor(int posX, int posY);

#endif

