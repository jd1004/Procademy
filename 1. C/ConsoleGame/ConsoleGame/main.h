#pragma once

#ifndef __MAIN__
#define __MAIN__

#define ENEMY_WIDTH 7
#define ENEMY_HEIGHT 3

#define BULLET_MAX 10
#define ENEMY_BULLET_MAX 10

struct User {
	int x;
	int y;
	int hp;
	bool flag;
};

struct Bullet {
	int x;
	int y;
	int type;		// 1플레이어		2적		0 null
	bool flag;		// 존재
};

struct Enemy {
	int x;
	int y;
	bool direction;
	bool flag;
	Bullet bullet;
};

User user;
Enemy enemy[ENEMY_HEIGHT][ENEMY_WIDTH];
Bullet bullet[BULLET_MAX];

char screenBuffer[SCREEN_HEIGHT][SCREEN_WIDTH];

// 버퍼 내용을 화면으로 찍어줌
// 적군, 아군, 총알 등을 screenBuffer에 넣고 1프레임이 끝나는 마지막에 호출하여 버퍼->화면 그림
void BufferFlip();


// 화면 버퍼 지워줌
// 매 프레임 그리기 직전에 버퍼 지워줌(잔상제거)
void BufferClear();


// 버퍼의 특정 위치에 원하는 문자 출력
// 입력받은 x,y에 아스키코드 하나 출력
void SpriteDraw(int x, int y, char sprite);

// 키 입력
void Key();

void InitUser();

void Shoot();

void InitEnemy();

void MoveEnemy();

void InitBullet();

void DrawMap();

void CrashCheck();

bool GameClearCheck();

void InitEnemyBullet();

void EnemyShoot();

bool GameOverCheck();

#endif


//--------------------------------------------------------------------
// 화면 깜빡임을 없애기 위한 화면 버퍼.
// 게임이 진행되는 상황을 매번 화면을 지우고 비행기 찍고, 지우고 찍고,
// 하게 되면 화면이 깜빡깜빡 거리게 된다.
//
// 그러므로 화면과 똑같은 크기의 메모리를 할당한 다음에 화면에 바로 찍지않고
// 메모리(버퍼)상에 그림을 그리고 메모리의 화면을 그대로 화면에 찍어준다.
//
// 이렇게 해서 화면을 매번 지우고, 그리고, 지우고, 그리고 하지 않고
// 메모리(버퍼)상의 그림을 화면에 그리는 작업만 하게 되어 깜박임이 없어진다.
//
// 버퍼의 각 줄 마지막엔 NULL 을 넣어 문자열로서 처리하며, 
// 한줄한줄을 printf 로 찍어나갈 것이다.
//
// for ( N = 0 ~ height )
// {
// 	  cs_MoveCursor(0, N);
//    printf(szScreenBuffer[N]);
// }
//
// 줄바꿈에 printf("\n") 을 쓰지 않고 커서좌표를 이동하는 이유는
// 화면을 꽉 차게 출력하고 줄바꿈을 하면 2칸이 내려가거나 화면이 밀릴 수 있으므로
// 매 줄 출력마다 좌표를 강제로 이동하여 확실하게 출력한다.
//--------------------------------------------------------------------

/*
int g_iX = 0;

void main(void)
{
cs_Initial();
Buffer_Clear();
//--------------------------------------------------------------------
// 게임의 메인 루프
// 이 루프가  1번 돌면 1프레임 이다.
//--------------------------------------------------------------------
int iX = 0;
while (1)
{
iX++;

// 스크린 버퍼를 지움
Buffer_Clear();

// 스크린 버퍼에 스프라이트 출력
Sprite_Draw(iX, 10, 'A');

// 스크린 버퍼를 화면으로 출력
Buffer_Flip();
// 프레임 맞추기용 대기 10 Frame
Sleep(100);
}
}
*/