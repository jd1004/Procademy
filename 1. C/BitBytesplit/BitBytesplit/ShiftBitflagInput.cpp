#include <stdio.h>
#include <Windows.h>

/*
	unsigned short (16bit) ������ �� ��Ʈ�� ��Ʈ�� �ϱ�

	- unsigned short ���� = 0 ���� �ʱⰪ ����.
	- Ű����� 1 ~ 16�� ��Ʈ �ڸ� �Է��� ����
	- 1 / 0  �� ����ڷκ��� �޾Ƽ� ������ �ڸ��� ��Ʈ�� 0 �Ǵ� 1�� �ٲ���.

	- �ٸ� ��ġ�� �Էµ� ���� �����ʹ� ������ �Ǿ�� ��
*/
int main()
{
	unsigned char num = 40;

	printf("%d �� ���̳ʸ� : ", num);
	for (int i = 7; i >= 0; i--) {
		printf("%d", (num >> i) & 1);
	}
	puts("");

	system("pause");

	return 0;
}
