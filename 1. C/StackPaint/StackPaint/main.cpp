#include <stdio.h>
#include <windows.h>
#include "stack.h"

#define MAP_HEIGHT 5
#define MAP_WIDTH 10

char OriginalMap[MAP_HEIGHT][MAP_WIDTH] = {
	{ ' ', '0' , '0' , '0' , '0', ' ' , ' ' , '0' , '0', '0' },
	{ '0', ' ' , '0' , '0' , '0', '0' , '0' , '0' , '0', '0' },
	{ ' ', ' ' , '0' , '0' , '0', '0' , '0' , '0' , '0', '0' },
	{ '0', ' ' , '0' , ' ' , '0', '0' , '0' , '0' , ' ', '0' },
	{ '0', ' ' , '0' , ' ' , ' ', '0' , '0' , ' ' , ' ', ' ' }
};

char MapBuffer[MAP_HEIGHT][MAP_WIDTH];
Stack stack;

void Draw();
void Do();

int main()
{
	Init(&stack);

	bool bSave = true;

	while (1)
	{
		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				MapBuffer[i][j] = OriginalMap[i][j];
			}
		}

		Draw();
		Sleep(100);

		Do();
		Sleep(100);
	}

	return 0;
}

void Draw()
{
	system("cls");

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			printf("%c", MapBuffer[i][j]);
		}
		printf("\n");
	}
}

void Do()
{
	int i = 5;
	int j = 5;
	bool error = true;

	Push(&stack, i, j);

	while (1)
	{
		if (MapBuffer[i][j] == '.' || MapBuffer[i][j] == ' ')
			error = Pop(&stack, &i, &j);

		if (error == false)
			break;

		else if (MapBuffer[i][j] == '0')
		{
			MapBuffer[i][j] = '.';
			Draw();
		}

		while (1)
		{
			// »óÇÏÁÂ¿ì
			if (MapBuffer[i - 1][j] == '0' && i - 1 >= 0)
			{
				i--;
				Push(&stack, i, j);
			}
			else if (MapBuffer[i + 1][j] == '0' && i < MAP_HEIGHT)
			{
				i++;
				Push(&stack, i, j);
			}
			else if (MapBuffer[i][j - 1] == '0' && j - 1 >= 0)
			{
				j--;
				Push(&stack, i, j);
			}
			else if (MapBuffer[i][j + 1] == '0' && j < MAP_WIDTH)
			{
				j++;
				Push(&stack, i, j);
			}

			break;
		}
	}
}