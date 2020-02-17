#include <stdio.h>
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
	unsigned char num = 40;

	printf("%d 의 바이너리 : ", num);
	for (int i = 7; i >= 0; i--) {
		printf("%d", (num >> i) & 1);
	}
	puts("");

	system("pause");

	return 0;
}
