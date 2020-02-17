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
	int type;		// 1�÷��̾�		2��		0 null
	bool flag;		// ����
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

// ���� ������ ȭ������ �����
// ����, �Ʊ�, �Ѿ� ���� screenBuffer�� �ְ� 1�������� ������ �������� ȣ���Ͽ� ����->ȭ�� �׸�
void BufferFlip();


// ȭ�� ���� ������
// �� ������ �׸��� ������ ���� ������(�ܻ�����)
void BufferClear();


// ������ Ư�� ��ġ�� ���ϴ� ���� ���
// �Է¹��� x,y�� �ƽ�Ű�ڵ� �ϳ� ���
void SpriteDraw(int x, int y, char sprite);

// Ű �Է�
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
// ȭ�� �������� ���ֱ� ���� ȭ�� ����.
// ������ ����Ǵ� ��Ȳ�� �Ź� ȭ���� ����� ����� ���, ����� ���,
// �ϰ� �Ǹ� ȭ���� �������� �Ÿ��� �ȴ�.
//
// �׷��Ƿ� ȭ��� �Ȱ��� ũ���� �޸𸮸� �Ҵ��� ������ ȭ�鿡 �ٷ� �����ʰ�
// �޸�(����)�� �׸��� �׸��� �޸��� ȭ���� �״�� ȭ�鿡 ����ش�.
//
// �̷��� �ؼ� ȭ���� �Ź� �����, �׸���, �����, �׸��� ���� �ʰ�
// �޸�(����)���� �׸��� ȭ�鿡 �׸��� �۾��� �ϰ� �Ǿ� �������� ��������.
//
// ������ �� �� �������� NULL �� �־� ���ڿ��μ� ó���ϸ�, 
// ���������� printf �� ���� ���̴�.
//
// for ( N = 0 ~ height )
// {
// 	  cs_MoveCursor(0, N);
//    printf(szScreenBuffer[N]);
// }
//
// �ٹٲ޿� printf("\n") �� ���� �ʰ� Ŀ����ǥ�� �̵��ϴ� ������
// ȭ���� �� ���� ����ϰ� �ٹٲ��� �ϸ� 2ĭ�� �������ų� ȭ���� �и� �� �����Ƿ�
// �� �� ��¸��� ��ǥ�� ������ �̵��Ͽ� Ȯ���ϰ� ����Ѵ�.
//--------------------------------------------------------------------

/*
int g_iX = 0;

void main(void)
{
cs_Initial();
Buffer_Clear();
//--------------------------------------------------------------------
// ������ ���� ����
// �� ������  1�� ���� 1������ �̴�.
//--------------------------------------------------------------------
int iX = 0;
while (1)
{
iX++;

// ��ũ�� ���۸� ����
Buffer_Clear();

// ��ũ�� ���ۿ� ��������Ʈ ���
Sprite_Draw(iX, 10, 'A');

// ��ũ�� ���۸� ȭ������ ���
Buffer_Flip();
// ������ ���߱�� ��� 10 Frame
Sleep(100);
}
}
*/