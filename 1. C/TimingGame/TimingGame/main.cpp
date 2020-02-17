#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

//# Ÿ�̹� ���߱� ����

int g_Timing[] = { 3, 6, 9, 12, 15 };

// �ʿ� �ش��ϴ� ���� �迭�� �־�ΰ�, �� �ð��� Ÿ�̹� �����ͷ� ��.
// �ڷ� �� ���� ū ���� �ִ°� ��Ģ���� ��.
//
// - ������ ��
//
// 1. ȭ�� ��ܿ� �ð��� ǥ�õ�.  ��:�и�������   (00:000  ���� �ڸ��� ����)
// 2. �Ʒ����� �� Ű Ÿ�̹��� ������ �ش� Ÿ�ֿ̹� �������� ����� ǥ��
// 3. �ƹ��� Ű�� ������ �ʰ� ���� �ð��� 1�� �̻� ������ �ڵ����� fail ó��.
// 4. ����ڰ� Ű�� ������ �ش� �ð��� üũ�Ͽ� ���� ������ ���� ���� Ÿ�̹��� ����� ȭ�鿡 ǥ�õ�.
//
// CLOCKS_PER_SEC / 4 �� ��ġ�� 1�ܰ�� �ִ� 4�ܰ� ������ ������ Great, Good, Nogood, Bad �ܰ� ����.
// ������� ����, + - ��� �ش��. 

void main()
{

	clock_t time;
	int check[5] = { 0 };
	int count = 0;

	while (count < 5)
	{
		double time = (double)clock() / CLOCKS_PER_SEC;

		printf("%006.3f Sec\n", time);

		if (_kbhit())
		{
			_getch();

			for (int i = count; i <= count; i++)
			{
				if (fabs(time - (double)g_Timing[i]) <= 0.25)
				{
					check[i] = 4;
				}
				else if (fabs(time - (double)g_Timing[i]) <= 0.5)
				{
					check[i] = 3;
				}
				else if (fabs(time - (double)g_Timing[i]) <= 0.75)
				{
					check[i] = 2;
				}
				else if (fabs(time - (double)g_Timing[i]) <= 1)
				{
					check[i] = 1;
				}
				else if (fabs(time - (double)g_Timing[i]) > 1)
				{
					check[i] = -1;
				}
			}
			count++;
		}
		else
		{
			for (int i = 0; i < 5; i++)
			{
				if (check[i] != 1 && check[i] != 2 && check[i] != 3 && check[i] != 4 && check[i] != -1 && time - (double)g_Timing[i] > 1)
				{
					check[i] = -1;
				}
			}
		}

		for (int i = 0; i < 5; i++)
		{
			printf("\n%2d Sec : ", g_Timing[i]);

			switch (check[i])
			{
			case 1:
				printf("Bad");
				break;

			case 2:
				printf("Nogood");
				break;

			case 3:
				printf("Good");
				break;

			case 4:
				printf("Great");
				break;

			case -1:
				printf("Fail");
				break;

			default:
				break;
			}

		}

		system("cls");

		Sleep(1);
	}

}
