#include <stdio.h>
#include <Windows.h>

#define MAP_HEIGHT 5
#define MAP_WIDTH 10

void Draw(int a, int b, char c);

char Map[MAP_HEIGHT][MAP_WIDTH] = {
	{ ' ', '0' , '0' , '0' , '0', ' ' , ' ' , '0' , '0', '0' },
	{ '0', ' ' , '0' , '0' , '0', '0' , '0' , '0' , '0', '0' },
	{ ' ', ' ' , '0' , '0' , '0', '0' , '0' , '0' , '0', '0' },
	{ '0', ' ' , '0' , ' ' , '0', '0' , '0' , '0' , ' ', '0' },
	{ '0', ' ' , '0' , ' ' , ' ', '0' , '0' , ' ' , ' ', ' ' }
};

int main()
{

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			printf("%c", Map[i][j]);
		}
		puts("");
	}

	Draw(3, 2, '.');

	printf("\n\n\n");

	return 0;
}

void Draw(int a, int b, char c)
{
	if (Map[b][a] == ' ' || Map[b][a] == c)return;
	if (a < 0)return;
	if (a > MAP_WIDTH)return;
	if (b < 0)return;
	if (b > MAP_HEIGHT)return;

	Map[b][a] = c;

	system("cls");

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			printf("%c", Map[i][j]);
		}
		puts("");
	}

	Draw(a - 1, b, c);
	Draw(a + 1, b, c);
	Draw(a, b - 1, c);
	Draw(a, b + 1, c);
	Sleep(20);
}


