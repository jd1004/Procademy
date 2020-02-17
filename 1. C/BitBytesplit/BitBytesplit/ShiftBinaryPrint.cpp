#include <stdio.h>
#include <math.h>
#include <Windows.h>

/*
	unsigned short (16bit) 변수의 각 비트를 컨트롤 하기

	 - unsigned short 변수 = 0 으로 초기값 가짐.
	 - 키보드로 1 ~ 16의 비트 자리 입력을 받음
	 - 1 / 0  을 사용자로부터 받아서 지정된 자리의 비트를 0 또는 1로 바꿔줌.

	 - 다른 위치에 입력된 기존 데이터는 보존이 되어야 함
*/

int main()
{
	unsigned short num = 0;
	int input1, input2;

	while (1)
	{
		printf("비트위치: ");
		scanf_s("%d", &input1);

		printf("OFF/ON [0,1] : ");
		scanf_s("%d", &input2);

		int j = pow(2, input1 - 1);

		if (input2 == 0)
		{
			num = num & ~j;
		}
		else
		{
			num = num | j;
		}

		for (int i = 15; i >= 0; i--)
		{
			if (((num >> i) & 1) == 1)
			{ 
				printf("%d 번 Bit : ON\n", i + 1);
			}
			else
			{
				printf("%d 번 Bit : OFF\n", i + 1);
			}

		}
		puts("");
	}
	system("pause");

	return 0;
}