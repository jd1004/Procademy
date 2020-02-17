#include <stdio.h>
#include <Windows.h>
#include <math.h>

int main()
{
	double dRadian = 0;

	while (1)
	{
		for (int i = 0; i <= 180; i += 5) {

			dRadian = sin(i * 3.14 / 180);

			for (int j = 1; j <= dRadian * 75; j++)
			{
				printf("*");
			}
			printf("\n");
			Sleep(50);
		}
	}

	return 0;
}