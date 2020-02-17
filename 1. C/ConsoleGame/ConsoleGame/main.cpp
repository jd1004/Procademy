#include <stdio.h>
#include <conio.h>
#include <memory.h>
#include <Windows.h>
#include <time.h>
#include "console.h"
#include "main.h"

void main()
{
	ConsoleInitial();
	BufferClear();
	InitUser();
	InitEnemy(); 
	InitBullet();
	InitEnemyBullet();
	DrawMap();

	while (1)
	{
		BufferClear();
		Key();

		MoveEnemy();
		EnemyShoot();
		screenBuffer[user.y][user.x] = 'A';
		
		Shoot();
		CrashCheck();
		
		BufferFlip();
		
		if (GameClearCheck()) {
			break;
		}

		if (GameOverCheck()) {
			break;
		}
		Sleep(1);
	}
	
	getchar();
	
}

void BufferFlip()
{
	for (int i = 1; i < SCREEN_HEIGHT; i++) {

		ConsoleMoveCursor(2, i);

		for (int j = 2; j < SCREEN_WIDTH ; j++) {
			printf("%c", screenBuffer[i][j]);
		}
	}
}

void BufferClear()
{
	for (int i = 1; i < SCREEN_HEIGHT; i++) {
		for (int j = 2; j < SCREEN_WIDTH ; j++) {
			screenBuffer[i][j] = ' ';
		}
	}
}

void SpriteDraw(int x, int y, char sprite)
{
	screenBuffer[y][x] = sprite;
}

void Key()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8001){
		if (user.x > 2) {
			user.x -= 1;
			screenBuffer[user.y][user.x] = 'A';
		}
	}
	
	if (GetAsyncKeyState(VK_RIGHT) & 0x8001) {
		if (user.x < SCREEN_WIDTH - 1) {
			user.x += 1;
			screenBuffer[user.y][user.x] = 'A';
		}
	}

	if (GetAsyncKeyState(VK_UP) & 0x8001) {
		if (user.y > 1) {
			user.y -= 1;
			screenBuffer[user.y][user.x] = 'A';
		}
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8001) {
		if (user.y < SCREEN_HEIGHT - 1) {
			user.y += 1;
			screenBuffer[user.y][user.x] = 'A';
		}
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8001) {
		
		for (int i = 0; i < BULLET_MAX; i++) {
			if (bullet[i].flag == false && bullet[i].type == 0) {
				bullet[i].x = user.x;
				bullet[i].y = user.y;
				bullet[i].type = 1;
				bullet[i].flag = true;
				break;
			}
		}
	}
}

void InitUser()
{
	user.x = 42;
	user.y = 25;
	user.hp = 100;
	user.flag = true;
}

void Shoot()
{
	for (int i = 0; i < BULLET_MAX; i++) {

		if (bullet[i].flag == true && bullet[i].type == 1) {

			if (bullet[i].y <= 0) {
				bullet[i].x = 0;
				bullet[i].y = 0;
				bullet[i].type = 0;
				bullet[i].flag = false;
			}
			else {
				bullet[i].y -= 1;
				SpriteDraw(bullet[i].x, bullet[i].y, 'o');
			}

		}
	}
}

void InitEnemy()
{
	for (int i = 0; i < ENEMY_HEIGHT ; i++) {
		for (int j = 0; j < ENEMY_WIDTH; j++) {
			enemy[i][j].x = 5 * j + 20;
			enemy[i][j].y = 5 * i + 5;
			enemy[i][j].direction = true;
			enemy[i][j].flag = true;
		}
	}
}

void MoveEnemy()
{
	if (enemy[0][0].x == 10) {
		for (int i = 0; i < ENEMY_HEIGHT; i++) {
			for (int j = 0; j < ENEMY_WIDTH ; j++) {
				enemy[i][j].direction = true;
			}
		}
	}

	if (enemy[0][9].x == SCREEN_WIDTH - 26) {
		for (int i = 0; i < ENEMY_HEIGHT; i++) {
			for (int j = 0; j < ENEMY_WIDTH; j++) {
				enemy[i][j].direction = false;
			}
		}
	}


	for(int i = 0; i < ENEMY_HEIGHT; i++) {
		for (int j = 0; j < ENEMY_WIDTH; j++) {
			if (enemy[i][j].direction) {
				enemy[i][j].x += 1;
			}
			else {
				enemy[i][j].x -= 1;
			}

			if(enemy[i][j].flag==true)
				SpriteDraw(enemy[i][j].x, enemy[i][j].y, '@');
		}
	}

}

void InitBullet()
{
	for (int i = 0; i < BULLET_MAX; i++) {
		bullet[i].type = 0;
		bullet[i].flag = false;
	}
}

void DrawMap()
{
	ConsoleMoveCursor(0, 0);
	printf("¦£");

	for (int i = 0; i < SCREEN_WIDTH ; i++) {
		printf("¦¡");
	}

	for (int i = 1; i < SCREEN_HEIGHT; i++) {
		ConsoleMoveCursor(0, i);
		printf("¦¢");
	}

	ConsoleMoveCursor(0, SCREEN_HEIGHT);
	printf("¦¦");

	ConsoleMoveCursor(SCREEN_WIDTH, 0);
	printf("¦¤");

	for (int i = 1; i < SCREEN_HEIGHT; i++) {
		ConsoleMoveCursor(SCREEN_WIDTH, i);
		printf("¦¢");
	}

	ConsoleMoveCursor(SCREEN_WIDTH, SCREEN_HEIGHT);
	printf("¦¥");

	for (int i = 1; i < SCREEN_WIDTH; i++) {
		ConsoleMoveCursor(i, SCREEN_HEIGHT);
		printf("¦¡");
	}

	ConsoleMoveCursor(100, 4);
	printf("HP: %d", user.hp);
}

void CrashCheck()
{
	for (int j = 0; j < ENEMY_HEIGHT; j++) {
		for (int k = 0; k < ENEMY_WIDTH; k++) {
			for (int i = 0; i < BULLET_MAX; i++) {
				if (bullet[i].x == enemy[j][k].x && bullet[i].y == enemy[j][k].y && enemy[j][k].flag == true) {
				
					bullet[i].x = 0;
					bullet[i].y = 0;
					bullet[i].type = 0;
					bullet[i].flag = false;					
					enemy[j][k].flag = false;
				}

			}
		}
	}


	for (int i = 0; i < ENEMY_HEIGHT; i++) {
		for (int j = 0; j < ENEMY_WIDTH; j++) {

			if (enemy[i][j].flag == true) {

				if (enemy[i][j].bullet.x == user.x && enemy[i][j].bullet.y == user.y) {

					user.hp -= 10;

					ConsoleMoveCursor(100, 4);
					printf("HP: %d   ", user.hp);
				}
			}
		}
	}
}

bool GameClearCheck()
{
	int count = 0;
	for (int i = 0; i < ENEMY_HEIGHT; i++) {
		for (int j = 0; j < ENEMY_WIDTH; j++) {
			
			if (enemy[i][j].flag == false) {
				count++;
			}
		}
	}

	if (count == ENEMY_HEIGHT*ENEMY_WIDTH) {
		BufferClear();
		BufferFlip();
		ConsoleMoveCursor(40, 16);
		printf("Game Clear!!");
		return true;
	}
	return false;
}

void InitEnemyBullet()
{
	/*for (int i = 0; i < ENEMY_BULLET_MAX; i++) {
		
		enemyBullet[i].type = 2;
		enemyBullet[i].flag = false;
	}*/

	for (int i = 0; i < ENEMY_HEIGHT; i++) {
		for (int j = 0; j < ENEMY_WIDTH; j++) {
			enemy[i][j].bullet.x = enemy[i][j].x;
			enemy[i][j].bullet.y = enemy[i][j].y;
			enemy[i][j].bullet.type = 2;
			enemy[i][j].bullet.flag = true;
		}
	}
}

void EnemyShoot()
{
	for (int i = 0; i < ENEMY_HEIGHT; i++) {
		for (int j = 0; j < ENEMY_WIDTH; j++) {

			if (enemy[i][j].flag == true) {
			
				if (enemy[i][j].bullet.flag == true) {

					if (enemy[i][j].bullet.y >= SCREEN_HEIGHT - 1) {
						enemy[i][j].bullet.x = enemy[i][j].x;
						enemy[i][j].bullet.y = enemy[i][j].y;
					}
					else {
						enemy[i][j].bullet.y += 1;
						SpriteDraw(enemy[i][j].bullet.x, enemy[i][j].bullet.y, '*');
					}


				}
			}
		}
	}
}

bool GameOverCheck()
{
	if (user.hp == 0) {

		BufferClear();
		BufferFlip();
		ConsoleMoveCursor(40, 16);
		printf("Game Over!!");
		return true;
	}
	return false;
}