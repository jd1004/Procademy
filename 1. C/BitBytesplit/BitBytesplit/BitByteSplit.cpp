#include <stdio.h>
#include <Windows.h>

/*
	unsigned int (32bit) 변수를 바이트 단위로 사용하기

	- unsigned int 변수 = 0 초기값 가짐
	- 키보드로 1 ~ 4 의 바이트 위치를 입력 받고
	- 해당 위치에 넣을 데이터 0 ~ 255 를 입력 받음
	- 사용자가 입력한 바이트 위치에 해당 값을 넣음

	- 데이터가 입력 되면 바이트 단위로 쪼개서 출력 & 4바이트 16진수 출력
	- 기존 데이터는 보존이 되어야 하며
	- 입력된 바이트 위치의 데이터는 기존 값을 지우고 넣음.
*/

int main()
{
	unsigned int num = 0;
	int input1, input2;

	while (1)
	{
		printf("위치 (1~4) : ");
		scanf_s("%d", &input1);

		printf("값 [0~255] : ");
		scanf_s("%d", &input2);

		if (num >> ((input1 - 1) * 8) & 255)
		{
			num = num & ~(255 << ((input1 - 1) * 8));
		}

		num = num | (input2 << ((input1 - 1) * 8));

		for (int i = 0; i < 4; i++) {
			printf("%d 번째 바이트 값 : %d\n", i + 1, (num >> (i * 8)) & 255);
		}

		printf("전체 4바이트 값 : 0x%08x\n\n", num);

	}
	system("pause");

	return 0;
}