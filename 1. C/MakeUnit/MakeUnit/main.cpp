#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include "queue.h"

void Logic();
void Render();

int main()
{
	int shutdown = 0;

	while (1)
	{
		if (shutdown == 1) break;

		if (_kbhit())
		{
			char key = _getch();

			switch (key)
			{
			case '1':
				UNIT unit;
				unit.Time = GetTickCount64();
				Enqueue(unit);
				break;

			case '2':
				shutdown = 1;
				break;
			default:
				break;
			}
		}

		Logic();

		Render();

		system("cls");
	}

	return 0;
}


void Logic()
{
	if (Peek(Queue, 0) != 0)
	{
		int first, last;

		first = (Front + 1) % N;
		last = (Rear + 1) % N;

		while (first != last)
		{
			if (GetTickCount64() - Queue[first].Time >= 5000)
			{
				Dequeue(Queue);
			}
			first = (first + 1) % N;
		}

	}

}

void Render()
{
	printf("1. À¯´Ö»ý¼º			2. Á¾·á\n");
	printf("======================================\n");

	int first, last;

	first = (Front + 1) % N;
	last = (Rear + 1) % N;

	while (first != last)
	{
		printf("À¯´Ö %lld %% \n", (GetTickCount64() - Queue[first].Time) / 50);
		first = (first + 1) % N;
	}
	puts("");

	Sleep(100);

}