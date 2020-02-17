#include <stdio.h>
#include <Windows.h>

/*
	unsigned int (32bit) ������ ����Ʈ ������ ����ϱ�

	- unsigned int ���� = 0 �ʱⰪ ����
	- Ű����� 1 ~ 4 �� ����Ʈ ��ġ�� �Է� �ް�
	- �ش� ��ġ�� ���� ������ 0 ~ 255 �� �Է� ����
	- ����ڰ� �Է��� ����Ʈ ��ġ�� �ش� ���� ����

	- �����Ͱ� �Է� �Ǹ� ����Ʈ ������ �ɰ��� ��� & 4����Ʈ 16���� ���
	- ���� �����ʹ� ������ �Ǿ�� �ϸ�
	- �Էµ� ����Ʈ ��ġ�� �����ʹ� ���� ���� ����� ����.
*/

int main()
{
	unsigned int num = 0;
	int input1, input2;

	while (1)
	{
		printf("��ġ (1~4) : ");
		scanf_s("%d", &input1);

		printf("�� [0~255] : ");
		scanf_s("%d", &input2);

		if (num >> ((input1 - 1) * 8) & 255)
		{
			num = num & ~(255 << ((input1 - 1) * 8));
		}

		num = num | (input2 << ((input1 - 1) * 8));

		for (int i = 0; i < 4; i++) {
			printf("%d ��° ����Ʈ �� : %d\n", i + 1, (num >> (i * 8)) & 255);
		}

		printf("��ü 4����Ʈ �� : 0x%08x\n\n", num);

	}
	system("pause");

	return 0;
}