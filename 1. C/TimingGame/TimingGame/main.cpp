#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

//# 타이밍 맞추기 게임

int g_Timing[] = { 3, 6, 9, 12, 15 };

// 초에 해당하는 값을 배열에 넣어두고, 이 시간을 타이밍 데이터로 씀.
// 뒤로 갈 수록 큰 값을 넣는걸 원칙으로 함.
//
// - 컨텐츠 부
//
// 1. 화면 상단에 시간이 표시됨.  초:밀리세컨드   (00:000  으로 자리수 맞춤)
// 2. 아래에는 각 키 타이밍의 정보와 해당 타이밍에 성공여부 결과를 표시
// 3. 아무런 키를 누르지 않고 지정 시간을 1초 이상 넘으면 자동으로 fail 처리.
// 4. 사용자가 키를 누르면 해당 시간을 체크하여 오차 범위에 따라서 지정 타이밍의 결과가 화면에 표시됨.
//
// CLOCKS_PER_SEC / 4 한 수치를 1단계로 최대 4단계 까지의 오차로 Great, Good, Nogood, Bad 단계 측정.
// 오차라는 것은, + - 모두 해당됨. 

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
