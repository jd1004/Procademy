#pragma once

// Windows �ܼ� ȭ�� Ŀ�� ����

#ifndef __CONSOLE__
#define __CONSOLE__



#define SCREEN_WIDTH 91			// �ܼ� ���� + NULL
#define SCREEN_HEIGHT 34		// �ܼ� ����


// �ܼ� ���� �غ�
void ConsoleInitial();

// �ܼ� ȭ�� Ŀ�� X, Y ��ǥ�� �̵�
void ConsoleMoveCursor(int posX, int posY);

#endif

